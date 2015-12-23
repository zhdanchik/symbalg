# -*- encoding: utf-8 -*-
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <aivlib/sphereT.hpp>
#include <math.h>
#include <stdio.h>
import symbalg
from symbalg.expressions import *
from symbalg.statements import *
from symbalg.funcs import *
from symbalg.ast_funcs import *
import sys,os,os.path
stms = {}

class part:
    pass

class Model:
    @function
    def calc():
        _[stms['omp']]
        For[i:0,"partarr.N"]
        _['part& p = partarr[i]']
        _[stms['calc']()]
        End
        time+=dt
 
    @function
    def start():
        For[i:0,"partarr.N"]
        _['part& p = partarr[i]']
        _[stms['start']()]
        End
        
    @function   
    def means():
        _[stms['mean_init']]

        For[i:0,"partarr.N"]
        _['part& p = partarr[i]']
        _[stms['mean_sum']]
        End
        _[stms['mean_norm']]

def mk_module(path, D, omp=False):

    old_format,BaseOp._format = BaseOp._format,'cpp'

    stms['calc'] = D['calc']
    stms['start'] = D['start']

    
    def means_retype(x):
        if isinstance(x, SetStm):
            if isinstance(x.lvalue, IndexOp):
                if x.lvalue._a._type == "double":
                    return SetStm(IndexOp(Var(x.lvalue._a._name, "aiv::mesh<double,%s>"%len(x.lvalue._b) ), x.lvalue._b), x.expr,x.op)
        return x
            
    stms['omp'] = '#pragma omp for scedule (dynamic) nowait' if omp  else ''

    default_vars = set([Var('time','double'),Var('partarr','aiv::array<part, 1>')])

    F = (D['calc']()+D['start']())
    struct_vars = collect_lvalues(F)
    mean_vars = collect_lvalues(D['means']()(_conv = means_retype))
    F+=D['means']()(_conv = means_retype) 
    global_vars = (collect_vars(F)|default_vars)-(struct_vars|mean_vars|collect_not_vars(F)) 
    Var.__cpp__ = lambda X: "p.%s"%X._name if X._name in map(lambda x:x._name,struct_vars) else X._name

#------------------------Init means---------------------------------------------------------------------------------------------------
    @statement
    def simple_init():
        arg = 0

    @statement
    def not_simple_init():
        For[i:0,arg.N]
        arg[i] = 0


    stms['mean_init'] = ListStm()
    for c in D['means']()._list:
        if isinstance(c.lvalue, IndexOp):  stms['mean_init']+=not_simple_init(arg = c.lvalue._a)
        else: stms['mean_init']+=simple_init(arg = c.lvalue)
#-------------------------------------------------------------------------------------------------------------------------------------
#------------------------Norm means---------------------------------------------------------------------------------------------------
    @statement
    def simple_norm():
        arg /= partarr.N[0]

    @statement
    def not_simple_norm():
        For[i:0,arg.N]
        arg[i] /= partarr.N[0] 
        for _i in range(count) : arg[i]/= arg.step[_i] 
    @statement
    def sphere_norm():
        For[i:0,arg.N]
        arg[i] /= 4 * M_PI * partarr.N[0] / (60 * 4 ^ arg.R) 

    stms['mean_norm'] = ListStm()
    for c in D['means']()._list:
        if isinstance(c.lvalue, IndexOp):
            if c.lvalue._a._type[:11] == "aiv::sphere":    stms['mean_norm']+=sphere_norm(arg = c.lvalue._a)
            else:         stms['mean_norm']+=not_simple_norm(count = len(c.lvalue._b) if type(c.lvalue._b) == tuple else 1, arg = c.lvalue._a)
        else: stms['mean_norm']+=simple_norm(arg = c.lvalue)
    
    
    def _toVctr(x):
        if isinstance(x,SetStm) and isinstance(x.lvalue,IndexOp):
            return SetStm( IndexOp(x.lvalue._a, CallOp(Var("Vctr"),x.lvalue._b)), x.expr, x.op) 
        return x
    stms['mean_sum'] = D['means']()(_conv = _toVctr)
#-------------------------------------------------------------------------------------------------------------------------------------



    module = ModuleContainer( eval(__name__))

    module.classes['part'].fields+=struct_vars
    module.classes['Model'].fields+=global_vars
    module.classes['Model'].fields+=mean_vars

    hpp,cpp = (module.out('hpp'),module.out('cpp'))
    mk = '''name=model
headers=model.hpp
modules=model.cpp
usedims=1
usearrs=P1-part-1

include aivlib/Makefile'''
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


