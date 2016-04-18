#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.magnu_str import *

#---------one-step scheme-------------------
@statement
def stage1():
    Heff = Hext + Hexch(m0) + Haniso(m0)
    m1 = m0 - h *( gamma*(m0%Heff)+alpha*(m0%(m0%Heff)))
    m1 /= m1.abs()

@statement
def stage2():
    m0 = m1
#---------RK4 scheme-------------------
@statement
def rk_stage1():
    Heff = Hext + Hexch(m0)
    dm0 = -h * ((m0%Heff) + alpha*(m0%(m0%Heff)))
    m1 = m0 + 0.5*dm0

@statement
def rk_stage2():
    Heff = Hext + Hexch(m0)
    dm1 = -h * ((m1%Heff) + alpha*(m1%(m1%Heff)))
    m2 = m0 + 0.5*dm1

@statement
def rk_stage3():
    Heff = Hext + Hexch(m0)
    dm2 = -h * ((m2%Heff) + alpha*(m2%(m2%Heff)))
    m3 = m0 + dm2

@statement
def rk_stage4():
    Heff = Hext + Hexch(m0)
    dm4 = -h * ((m3%Heff) + alpha*(m3%(m3%Heff)))
    m0 += (dm0+dm4)/6 + (dm1+dm2)/3
    m0/=m0.abs()
    gauss_rotate(m0,2*sqrt(alpha*T*h))



# mk_module("magnu_test", 
#           "latCubic",
#           Atom(m0='vctr<3>', m1='vctr<3>'),
#           "m0",
# 	      h='double', Hext='vctr<3>', gamma='double', alpha='double', # opisanie poley Model
# 	      step=[("stage1", stage1), ("stage2", stage2)] # opisanie metdow Model	
# )

mk_module("magnu_test", 
          "latCubic",
          Atom(m0='vctr<3>', dm0='vctr<3>', m1='vctr<3>', dm1='vctr<3>', m2='vctr<3>', dm2='vctr<3>', m3='vctr<3>'),
          "m0",
          h='double', Hext='vctr<3>', T='double', alpha='double', # opisanie poley Model
          stepRK4=[("rk_stage1", rk_stage1), ("rk_stage2", rk_stage2), ("rk_stage3", rk_stage3), ("rk_stage4", rk_stage4)] # opisanie metdow Model 
)

from magnu_test import *

fig1 = Cylinder(Vctr(0.,0.,20.), 10., 40.)
fig2 = Cube(Vctr(20.,20.,30.), 40.)

fig3 = Box(Vctr(-20.,0.,0.), 20., 80., 20.)

figs = SetFigures()
#figs.add(Cylinder(Vctr(10.,10.,20.), 10., 40.)) # --- не работает :(

figs.add(fig1)
figs.add(fig2)
figs.add(fig3)

M = Model()

M.init(fig1)

M.Hext = Indx(0.,0.,1.)
M.alpha = 0.01
M.gamma = 0.1
M.h = 0.05 
M.T = 1
M.set_J(0,0,1.)

tcount = 1000

M.simplestart(Vctr(1.,0.,0.))

S = Ofile("magnu_test/atoms.msh")
M.dump_head(S)
M.dump_data(S)

Stext = Ofile("magnu_test/diag.dat")
M.init_diag(Stext)
M.dump_diag(Stext)
for t in range(tcount):
    M.stepRK4()
    print '\r',"%s / %s" %(t+1, tcount), ;sys.stdout.flush()
    M.dump_diag(Stext)
    M.dump_data(S)

#gplt -3d -U 'M1z(M1x,M1y)@:3' magnu_test/M1.dat -ur 0:pi -vr 0:2*pi -para=y -fn 'sin(u)*cos(v),sin(u)*sin(v),cos(u)' -raw 'set view equal' -raw 'set border 4095' -cu : { -k '' } -lbx '' -lby '' -lbz '' -xt.-fr ' ' -yt.-fr ' ' -zt.-fr ' ' -nk -to tM1.pdf showcmd=okular -pv=y

#gplt -3d -U 'M1z(M1x,M1y)' magnu_test/M1.dat -ur 0:pi -vr 0:2*pi -para=y -fn 'sin(u)*cos(v),sin(u)*sin(v),cos(u)' -raw 'set view equal'

#1.5GB