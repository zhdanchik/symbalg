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

class Model():
    pass

class Atom():
    @mymethod
    def get_m(stage = "int"): #:inline
        pass
 

    # inline vctr<3> get_m(int stage) const { %(atom_get_m)s; }

class Cell():
    @myfield
    def atoms() : 
        _type = "Atom[cell_sz]";
        _value = 0;
    
    usage = "bool[cell_sz]"

class Model():
    tile_data="array<Cell,3>"
    arrJ = "double[cell_sz][cell_sz]"

class NbCR():
    dpos = "indx<3>"
    lattice = "int"

    @mymethod
    def NbCR():
        pass

    @mymethod
    def NbCR(l = "int", d = "indx<3>"):
        pass

    # NbCR( d, int l):dpos(d), lattice(l){}

class AAA():
    pass

def mk_module(path, D):
    old_format,BaseOp._format = BaseOp._format,'cpp'
    module = Module(eval(__name__))
    


    generate_1_module(module,path, False)
    BaseOp._format = old_format
 