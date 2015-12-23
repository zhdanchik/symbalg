#!/usr/bin/python
from symbalg.skeletons.stochastic import *

@statement
def start():
    X = 0
    Vx = 0

@statement
def calc():
    X += dt * .5 *Vx
    Vx +=  - dt * ((a * X + b * X * X * X) + Gamma * Vx) + sqrt(2.*Gamma*T*dt)*'rand_gauss()'
    X += dt * .5 *Vx

@statement
def means():
    M1X += X
    M2X += X*X
    
mk_module('mymodule', globals())
# clean_symbalg(globals()) #???

from mymodule import *

M = Model()

M.partarr.init(Indx(10000))

M.a=-1
M.b=1
M.Gamma=0.1
M.dt=0.1
M.T=0.1 

M.time=0

M.start()

means = open('mymodule/res.dat','w')
f =  Ofile('f.arr')
print>>means,'#:t M1x M2x'# M2x M1v M2v'

while M.time < 5./M.Gamma :
    M.calc()
    M.means()
    
    print>>means, M.time, M.M1X, M.M2X#, M.M1V, M.M2V
    # M.f.dump(f)
    print '\r', M.time, 5./M.Gamma, ; sys.stdout.flush()