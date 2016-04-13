#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.magnu_str import *

#---------one-step scheme-------------------
@statement
def stage1():
    Heff = Hext + Hexch(m0)
    m1 = m0 - h *( gamma*(m0%Heff)+alpha*(m0%(m0%Heff)))
    m1 /= m1.abs()

@statement
def stage2():
    m0 = m1
# #---------one-step scheme-------------------
# @statement
# def rk_stage1():
#     Heff = Hext + Hexch(m0)
#     dm0 = -h * (gamma * (m0%Heff) + alpha*(m0%(m0%Heff)))
#     m1 = m0 + 0.5*dm0

# @statement
# def rk_stage2():
#     Heff = Hext + Hexch(m0)
#     dm1 = -h * (gamma * (m1%Heff) + alpha*(m1%(m1%Heff)))
#     m2 = m0 + 0.5*dm1

# @statement
# def rk_stage3():
#     Heff = Hext + Hexch(m0)
#     dm2 = -h * (gamma * (m2%Heff) + alpha*(m2%(m1%Heff)))
#     m3 = m0 + dm2

# @statement
# def rk_stage3():
#     Heff = Hext + Hexch(m0)
#     dm2 = -h * (gamma * (m2%Heff) + alpha*(m2%(m1%Heff)))
#     m3 = m0 + dm2


@statement
def foo():
    m1 = m0 #fignya dlya primera

mk_module("magnu_test", Atom(m0='vctr<3>', m1='vctr<3>'),
	      h='double', Hext='vctr<3>', gamma='double', alpha='double', # opisanie poley Model
	      step=[("stage1", stage1), ("stage2", stage2)], foo=[("foo",foo)] # opisanie metdow Model	
)

from magnu_test import *

M = Model()
Nx, Ny, Nz = 20, 20, 40
M.data.init(Indx(Nx, Ny, Nz))

M.Hext = Indx(0.,0.,1.)
M.alpha = 0.01
M.gamma = 0.1
M.h = 0.05 

M.set_J(0,0,1.)

tcount = 1000

M.simplestart(Vctr(1.,0.,0.))

fdat = open("magnu_test/M1.dat","w")
fdat.write("#:t M1x M1y M1z\n")
fdat.write("%s %s\n"%(0, M.M1()))

for t in range(tcount):
    M.step()
    print '\r',"%s / %s" %(t+1, tcount), ;sys.stdout.flush()
    fdat.write("%s %s\n"%((t+1)*M.h, M.M1()))

#gplt -3d -U 'M1z(M1x,M1y)@:3' magnu_test/M1.dat -ur 0:pi -vr 0:2*pi -para=y -fn 'sin(u)*cos(v),sin(u)*sin(v),cos(u)' -raw 'set view equal' -raw 'set border 4095' -cu : { -k '' } -lbx '' -lby '' -lbz '' -xt.-fr ' ' -yt.-fr ' ' -zt.-fr ' ' -nk -to tM1.pdf showcmd=okular -pv=y

#gplt -3d -U 'M1z(M1x,M1y)' magnu_test/M1.dat -ur 0:pi -vr 0:2*pi -para=y -fn 'sin(u)*cos(v),sin(u)*sin(v),cos(u)' -raw 'set view equal'