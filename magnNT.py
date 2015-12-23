#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
#include <stdio.h>

import symbalg
#import new_stoh
from symbalg.expressions import *
from symbalg.statement import *
from symbalg.funcs import *

class Atom:
    m = H = 'vctr<3>[NT]'

class Cell:
    a = b = 'Atom'
    use_a = use_b = 'bool'

#def fact(): print '*****************************'

@statement
def for_each():
    For( i('long', value=0), i<'data.N', i+_ )
    pos('indx<3>', value=i%'data.N').push() 
    C('Cell&', value='data[pos]').push()
    print _act()() #Push(_act)
    End()
@statement
def dump_head():
    _['if( C.a_use ){ r = pos*vctr<3>(1);             S.fwrite( &r, sizeof(r) ); }']
    _['if( C.b_use ){ r = pos*vctr<3>(1)+vctr<3>(.5); S.fwrite( &r, sizeof(r) ); }']


class Model:
    data = 'array<Cell,3>'
    Hext = 'vctr<3>'
    gamma = alpha = T = h = 'double'
    count = 'int'

    @function
    def dump_head(S='Ostream&'): 
        zero('int', value=0).push() #??? 
        _['S.fwrite()  &zero, sizeof(int) )']
        Push("S.fwrite( &count, sizeof(int) ); vctr<3,float> r;")
        for_each(_act=dump_head)

    @function
    def dump_data(S='Ostream&'): 
        pass

    @function
    def calc(n_steps='int'):
        For(step('int',value=0), step<n_steps, step+_)
        End()


import moduleparser
moduleparser.parse(__name__)