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
from symbalg.generating import *

import sys,os,os.path

class Base_cell:
    pass

#:typedef Base_cell* pcell;

# class cell1(Base_cell): 
#     pass

class Base_tile:
    tile_data="aiv::array<pcell,3>"

    @function
    def start(): #:virtual
        pass
    @function
    def step_H(mmm="ptile", zmm="ptile", pmm="ptile", mzm="ptile", zzm="ptile", pzm="ptile", mpm="ptile", zpm="ptile", ppm="ptile", mmz="ptile", zmz="ptile", pmz="ptile", mzz="ptile", zzz="ptile", pzz="ptile", mpz="ptile", zpz="ptile", ppz="ptile", mmp="ptile", zmp="ptile", pmp="ptile", mzp="ptile", zzp="ptile", pzp="ptile", mpp="ptile", zpp="ptile", ppp="ptile"): #:virtual
        pass
    @function
    def step_m(): #:virtual
        pass
                
#:typedef Base_tile* ptile;

# class Sec1_tale(Base_tile):
#     @function
#     def start():
#         pass
class Model:
    pass

def mk_module(path, D):
    old_format,BaseOp._format = BaseOp._format,'cpp'

    F = sum(sum([dict(tile).values() for tile in D["Tiles"]],[]),ListStm())

    _dim = collect_dim(F)

    struct_vars = collect_lvalues(F)

    default_vars = set([Var('h','double'), Var('time','double')])

    global_vars = (collect_vars(F)|default_vars)-(struct_vars|collect_not_vars(F)) 

    print struct_vars
    print global_vars

    module = ModuleContainer( eval(__name__))
    for i,cell in enumerate(D["Cells"]):
        name = "cell%s"%i
        cnt = (16 + (float(i)/len(D["Cells"]))*(17-16)   )
        module.stuffs[(name,cnt)]=ClassContainer(name, [(Var(c[0],c[1]),"public",[]) for c in cell] ,[], parents = ["Base_cell"], counter = cnt)

    for n,i in module.stuffs: 
        if n=="Base_tile": module.stuffs[(n,i)].stuffs.append(("typedef Base_tile* ptile",0,"public"))

    print module.stuffs    
    for i,tile in enumerate(D["Tiles"]):
        name = "tile%s"%i
        cnt = (34 + (float(i)/len(D["Cells"]))*(35-34)   )
        module.stuffs[(name,cnt)]=ClassContainer(name, [] ,[
            MethodContainer("start", dict(tile)["start"], [], preffixes= []),
            MethodContainer("step_H", dict(tile)["step_H"], [Var(i+k+l,"ptile") for l in 'mzp' for k in 'mzp' for i in 'mzp'], preffixes= []),
            MethodContainer("step_m", dict(tile)["step_m"], [], preffixes= []),
            ], parents = ["Base_tile"], counter = cnt)
    
    for n,i in module.stuffs: 
        if n=="Model": 
            print [(v, "public", "static") for v in global_vars]
            module.stuffs[(n,i)].fields+=[(v, "public", ["static"]) for v in global_vars]
            module.stuffs[(n,i)].fields+=[(Var("data","aiv::array<ptile,3>"), "public", ["static"])]
    Var.__cpp__ = lambda X: "Model::%s"%X._name if X in global_vars else X._name
    

    mk = """name=model
headers=model.hpp
modules=model.cpp
usedims=1 %(dim)s
usearrs=PT%(dim)s-ptile-%(dim)s PC%(dim)s-pcell-%(dim)s

include aivlib/Makefile"""%{"dim":_dim}
    mk=''
    generate_1_module(module,path,mk)
    BaseOp._format = old_format
 