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

def generate_1_module_from_str(D, templates_path, folders, files, path, make = True):

    try: os.makedirs(path)
    except : pass
    
    for folder in folders:
        try: os.makedirs(os.path.join(path,folder))
        except:pass
    for fname in files:
        fstr = open(os.path.join(templates_path,fname), "r").read()%D
        if os.path.isfile(os.path.join(path,fname)):
            if fstr == open(os.path.join(path,fname),'r').read(): continue
        open(os.path.join(path,fname),'w').write(fstr)
    open(os.path.join(path,'__init__.py'),'w').write('from model import *')
    if make:
        tmp = os.path.abspath(os.curdir)
        os.chdir(path); os.system("make -f model.mk -j8"); os.chdir(tmp)


