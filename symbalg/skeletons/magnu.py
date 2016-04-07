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


#:class Model;

class Atom():
    @mymethod
    def get_m(_type = "vctr<3>", stage = "int"): #:inline const
        pass

    inline vctr<3> get_m(int stage) const { %(atom_get_m)s; } 
    
    @mymethod
    def step(stage = "int", model = "const Model &", Hexch = "const vctr<3> &"): #:inline
        For[stage:0,"stage_count"]
        For["indx<3>", pos,0, pos.less(data.N),_+pos]
        _["Cell &cell = data[pos]"]
        For[l:0,"cell_sz"]

        _["Atom &atom = cell.atoms[l]"]

        If["!atom.usage"]
        _["continue"]
        End

        _["vctr<3> Hexch"]

        If["calc_exch&(1<<stage)"]
        For[i:0,"nb_counts[l]"]

        _["const NbCR &nb = nb_arr[l][i]"]
        _["const Cell &cell2 = periodic_bc<7>(data, pos+nb.dpos)"]
        If["cell2.usage[nb.lattice]"]
        _["Hexch += cell2.atoms[nb.lattice].get_m(stage)*arrJ[l][nb.lattice]"]
        End

        End
        End

        End
        End
        End

@myfield
def cell_sz(_type = "int") : pass #:const
@myfield
def stage_count(_type = "int") : pass #:const
@myfield
def calc_exch(_type = "int") : pass #:const

class Cell():
    @myfield
    def atoms(_type = "Atom[cell_sz]") : pass
    @myfield
    def usage(_type = "bool[cell_sz]") : pass

class Model():
    @myfield
    def tile_data(_type = "array<Cell,3>") : pass
    @myfield
    def arrJ(_type = "double[cell_sz][cell_sz]") : pass

    @mymethod
    def get_J(_type = "double", l1 = "int", l2 = "int"): #:const
        Return[arrJ[l1][l2]];

    @mymethod
    def set_J(l1 = "int", l2 = "int", J = "double"): 
        arrJ[l1][l2] = J
        arrJ[l2][l1] = J

    @mymethod
    def step() : 
        pass

class NbCR():
    @myfield
    def dpos(_type = "indx<3>") : pass
    @myfield
    def lattice(_type = "int") : pass

    @mymethod
    def NbCR():
        pass
    
    @mymethod
    def NbCR(l = "int", d = "indx<3>"):
        pass

@myfield
def max_nb_count(_type = "int") : pass #:const
@myfield
def nb_counts(_type = "int[cell_sz]") : pass #:const
@myfield
def nb_arr(_type = "NbCR[cell_sz][max_nb_count]") : pass #:const


def mk_module(path, D):
    old_format,BaseOp._format = BaseOp._format,'cpp'
    module = Module(eval(__name__))
    


    generate_1_module(module,path, False)
    BaseOp._format = old_format
 