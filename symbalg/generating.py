# -*- encoding: utf-8 -*-
import os
def generate_1_module(module, path, make = True):

    hpp,cpp = (module.out('hpp'),module.out('cpp'))
    mk = """name=model
headers=model.hpp
modules=model.cpp

include aivlib/Makefile"""

    try: os.makedirs(path)
    except : pass

    for C in 'hpp cpp mk'.split():
        if os.path.isfile(path+'/model.'+C):
            if eval(C) == open(path+'/model.' + C,'r').read(): continue
        open(path+'/model.' + C,'w').write(eval(C))
    open(path+'/__init__.py','w').write('from model import *')
    if make:
        tmp = os.path.abspath(os.curdir)
        os.chdir(path); os.system("make -f model.mk -j8"); os.chdir(tmp)
