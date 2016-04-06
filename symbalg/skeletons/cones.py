# -*- encoding: utf-8 -*-
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
import symbalg
from symbalg.expressions import *
from symbalg.statements import *
from symbalg.funcs import *
from symbalg.ast_funcs import *
from symbalg.cone_funcs import *
import sys,os,os.path
stms = {}

class cell:
    pass

class Model():
    pass

def mk_module(path, D):

    old_format,BaseOp._format = BaseOp._format,'cpp'
    
    def Add_coords(obj, coords):
        if isinstance(obj,ListStm):
            tmplist = ListStm()
            for act in obj._list:
                tmpobj = act
                indxs = ()
                if isinstance(act,SetStm):
                    if isinstance(act.lvalue,IndexOp):
                        indxs = act.lvalue._b                    
                def _replacecoord(x):
                    if isinstance(x,Var):
                        if x._name == coords[coord]: return indxs[coord]+x
                    return x
                for coord in range(len(indxs)):tmpobj = tmpobj(_conv = _replacecoord)
                tmplist.append(tmpobj)
            return tmplist
        return obj


    sec_acts, starts = [], []
    cones = []
    for v in D.keys():
        if v[:8]=="calc_sec":
            if D[v].__name__ == "wrap": sec_acts.append(D[v])
        if v[:5]=="start":
            if D[v].__name__ == "wrap": starts.append((v,D[v]))
        if v[:9]=="calc_cone":
            if isinstance(D[v],ListStm): cones.append((v,Add_coords(D[v],['X','Y','Z'])))
    

    F =  reduce(lambda a,b:a[1]()+b[1](),starts,[0,ListStm()]) + reduce(lambda a,b:a()+b(),sec_acts,ListStm())
    _dim = 0
    for a in F._list:
        if isinstance(a,SetStm):
            if isinstance(a.lvalue, IndexOp):
                if _dim == 0 : _dim = len(a.lvalue._b)
                if _dim != len(a.lvalue._b): raise SymbalgError("Error in left values in acts. Not all vars have equal dimension")
    
    default_vars = set([Var('h','double'), Var('data','aiv::array<cell, %s>'%_dim)])
    struct_vars = collect_lvalues(F)
    global_vars = (collect_vars(F)|default_vars)-(struct_vars|collect_not_vars(F)) 


    IndexOp.__cpp__ = lambda X: "data_crop[Indx(%s)].%s"%(','.join(map(str,X._b)), X._a._name if X._name in map(lambda x:x._name,struct_vars) else X._a)
    
    presub = ListStm()
    presub.append("auto data_crop = data.crop( offset, data.N, Indx(%s))"%(','.join("1"*_dim)))
    # presub.append("auto data_crop = data")#.crop( offset, data.N, Indx(%s))"%(','.join("1"*_dim)))
    for i in range(_dim): presub.append("double %s = offset[%s]"%('XYZ'[i],i) )

    module = Module( eval(__name__))

    # print cones
    module.classes['cell'].fields+=struct_vars
    module.classes['Model'].fields+=global_vars

    module.classes['Model'].methods+=[Method(k, presub()+v(), [Var("offset","aiv::indx<%s>"%_dim)]) for k,v in starts]

    presub._list.insert(0,"double time = init_time")
    
    module.classes['Model'].methods+=[Method(cone[0], presub()+cone[1], [Var("init_time","double"),Var("offset","aiv::indx<%s>"%_dim)]) for cone in cones]
    
    # print module.classes['Model'].methods[0].body._list[0].__class__
    hpp,cpp = (module.out('hpp'),module.out('cpp'))
    mk = '''name=model
headers=model.hpp
modules=model.cpp
usedims=1
usearrs=C%s-cell-%s

include aivlib/Makefile'''%(_dim,_dim)
    try: os.makedirs(path)
    except : pass

    for C in 'hpp cpp mk'.split():
        if os.path.isfile(path+'/model.'+C):
            if eval(C) == open(path+'/model.' + C,'r').read(): continue
        open(path+'/model.' + C,'w').write(eval(C))
    open(path+'/__init__.py','w').write('from model import *')
        
    tmp = os.path.abspath(os.curdir)
    os.chdir(path); os.system("make -f model.mk"); os.chdir(tmp)

    BaseOp._format = old_format