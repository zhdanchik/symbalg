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

class cell1(Base_cell): 
    pass

class Base_tile:
    @function
    def start(): #:static
        pass

#:typedef Base_tile* ptile;

class Sec1_tale(Base_tile):
    @function
    def start():
        pass


def mk_module(path, D):

    old_format,BaseOp._format = BaseOp._format,'cpp'

    module = ModuleContainer( eval(__name__))

    mk = """"""

    generate_1_module(module,path,mk)

    BaseOp._format = old_format
 