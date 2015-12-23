# -*- encoding: utf-8 -*-
#include <aivlib/meshTD.hpp>

import symbalg
from symbalg.expressions import *
from symbalg.statements import *
from symbalg.funcs import *
from symbalg.ast_funcs import *
from symbalg.cone_funcs import *
import sys,os,os.path
stms = {}



class Base_cell():
    pass

class Base_tile():
    pass

class Model():
    pass
    
def mk_module(path, D):


    hpp,cpp = (module.out('hpp'),module.out('cpp'))
    mk = '''name=model
headers=model.hpp
modules=model.cpp
usedims=1 %(dim)s
usearrs=C%(dim)s-cell-%(dim)s

include aivlib/Makefile'''%{"dim":_dim}
    try: os.makedirs(path)
    except : pass

    for C in 'hpp cpp mk'.split():
        if os.path.isfile(path+'/model.'+C):
            if eval(C) == open(path+'/model.' + C,'r').read(): continue
        open(path+'/model.' + C,'w').write(eval(C))
    open(path+'/__init__.py','w').write('from model import *')
        
    tmp = os.path.abspath(os.curdir)
    os.chdir(path); os.system("make -f model.mk -j8"); os.chdir(tmp)

    BaseOp._format = old_format