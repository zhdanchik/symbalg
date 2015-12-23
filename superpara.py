#!/usr/bin/python
from symbalg.skeletons.stochastic import *
# from symbalg.expressions import *
# from symbalg.statements import *


@statement
def gauss_rotate():
    arg = rotate( rotate( arg, rand_alpha2PI*random(), arg%ort(arg)/(arg%ort(arg)).abs() ) , 2*sqrt(gamma*dt*T)*rand_gauss(), arg )

@statement
def start():
    m=Vctr(0,0,1)

@statement
def calc():
    m = rotop(m)(-alpha*dt*(Hext + A*sin(Omega*time) + k * (k*m)**2)).val
    m -= gamma * dt * (m % (m % (Hext + A*sin(Omega*time) + k * (k*m)**2)))
    # _[gauss_rotate(arg = m)]
    m = rotate( rotate( m, rand_alpha2PI*random(), m%ort(m)/(m%ort(m)).abs() ) , 2*sqrt(gamma*dt*T)*rand_gauss(), m )
    Hext._type = 'aiv::vctr<3>'
    A._type = 'aiv::vctr<3>'
    k._type = 'aiv::vctr<3>'
    m._type = 'aiv::vctr<3>'

@statement
def means():
    M1 += m
    M2 += m*m
    f[m] += One
    M1._type = 'aiv::vctr<3>'
    M2._type = 'aiv::vctr<3>'
    f._type = 'aiv::sphere<float>'


mk_module('Superpara', globals())

import Superpara
from Superpara import *
M = Model()

M.partarr.init(Indx(10000 )) #Num of particles in braces
M.f.init(2)  # recurcion level in '()'
M.dt = 0.01 #value after '='
M.Omega = 1  #value after '='
M.A = Vctr(1,0,0) #value after '='
M.gamma = 0.1 #value after '='
M.Hext = Vctr(0,0,1) #value after '='
M.k = Vctr(0,0,1) #value after '='
M.alpha =  1 #value after '='
M.T = 0.1
M.time = 0

filename = "sphere.sph"
file = Ofile(filename)
f2 = "res.dat"
file2 = open(f2,"w")
M.start()

print>>file2, "#:t M1x M1y M1z M2x M2y M2z"

while M.time <  30: #Calculation time after "<"
    M.calc()
    M.means()
    print '\r', M.time, ; sys.stdout.flush()
    M.f.dump(file)
    #print>>file2, "%s %s %s"%(M.time, M.M1, M.M2)
    print>>file2, "%s %s"%(M.time, M.M1)