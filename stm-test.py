from symbalg.expressions import *
from symbalg.statements import *
from symbalg.ast_funcs import *
#from symbalg.funcs import *


BaseOp.format = 'cpp'

@statement 
def body():
    a = 23

@statement 
def test():
    _[body(), body()]
    For['int',i,0, i<10, i+_]
    For[j:0, N, k]
    a += sin(b+c//k)**2 + gg(1,2,3)
    End
    a *= exp(i)
    _[body()]



def offset(step):
    def _offset(x):
        if isinstance(x, IndexOp) and type(x._b) is tuple: x._b = [i+step for i in x._b]
        return x
    return _offset

def crop(x):
    if isinstance(x, SetStm) and isinstance(x.lvalue, IndexOp) and type(x.lvalue._b) is tuple: return x if all([  k>0 for k in x.lvalue._b ]) else None
    if isinstance(x, Var) : 
        return Var(x._name+'1',x._type)
    return x

BaseOp.format = 'cpp'
# print test2()
# print test2()(_conv=crop)#(hh=1)
# print (test2()+test2()(_conv=offset(2)))(_conv=crop)





def cyclicshift(l,r, cycleindexes = True):
    def _cyclicshift(x):
        if isinstance(x, Var):
            for cycle in l.split():
                cycle = [cycle+c for c in r.split()]
                x = Var(cycle[(cycle.index(x._name)+1)  % len(cycle)],x._type) if x._name in cycle else x
        if isinstance(x, IndexOp) and type(x._b) is tuple and cycleindexes : 
            x._b = tuple([x._b[-1]] + list(x._b[:-1]))
        return x
    return _cyclicshift       




@statement
def E():
    Ex[0.,.5,.5][.5] = Ex[1.,.5,.5][-.5] + Cz*( By[1.,.5,0.][0.] -  By[1.,.5,1.][0.] ) + Cy*( Bz[1.,1.,.5][0.] - Bz[1.,0.,.5][0.] ) 
@statement    
def B():    
    Bx[.5,1.,1.][1.] = Bx[.5,1.,1.][0.] + Cz*( Ey[.5,1.,1.5][.5] - Ey[.5,1.,.5][.5] ) + Cy*( Ez[.5,.5,1.][.5] - Ez[.5,1.5,1.][.5] )

E1 = E()(_conv = cyclicshift('B E C','x y z'))
E2 = E1(_conv = cyclicshift('B E C','x y z'))

@statement
def All():
    _[B() + B()(_conv = cyclicshift('B E C','x y z')) + B()(_conv = cyclicshift('B E C','x y z'))(_conv = cyclicshift('B E C','x y z'))]
    _[E() + E()(_conv = cyclicshift('B E C','x y z')) + E()(_conv = cyclicshift('B E C','x y z'))(_conv = cyclicshift('B E C','x y z'))]

@statement
def Alle():
    _[E()+E1+E2]


@statement
def ttt():

    #For[i:0,"partarr.N"]
    qwe._type = 'doublesdad'
    _[tttt()(a=qwe, v=asd)] #(a = ff, h = ff, b=ff, c=ff)]
    _[tttt()(a=qwe, v=rty.asd)]
    v = _+a
    


@statement
def Indx_Call_Attr():
    a.v += h.q(b,c,1)%a
    g[y] = a[k]
    hh = (a1+a2).abs()
BaseOp._format = 'cpp'
print Indx_Call_Attr()
print collect_vars(Indx_Call_Attr())
print Indx_Call_Attr()._list[0].lvalue(a='b')
print Indx_Call_Attr()._list[0].lvalue(a='b')._b
print Indx_Call_Attr()._list[0].expr(b='g')
print Indx_Call_Attr()._list[1](k='g')