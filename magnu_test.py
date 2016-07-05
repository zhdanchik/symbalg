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



mk_module("magnu_test", 
          "latFCC4", 
          # "latFCC4_trans_1",
          Atom(m0='vctr<3>', m1='vctr<3>'),
          "m0",
	      h='double', Hext='vctr<3>', gamma='double', alpha='double', # opisanie poley Model
	      step=[("stage1", stage1), ("stage2", stage2)] # opisanie metdow Model	
)

# mk_module("magnu_test", 
#           "latCubic",
#           Atom(m0='vctr<3>', dm0='vctr<3>', m1='vctr<3>', dm1='vctr<3>', m2='vctr<3>', dm2='vctr<3>', m3='vctr<3>'),
#           "m0",
#           h='double', Hext='vctr<3>', T='double', alpha='double', # opisanie poley Model
#           stepRK4=[("rk_stage1", rk_stage1), ("rk_stage2", rk_stage2), ("rk_stage3", rk_stage3), ("rk_stage4", rk_stage4)] # opisanie metdow Model 
# )

from magnu_test import *
import math

fig1 = cylinder(Vctr(0.,0.,0.), Vctr(0., 1., 1.), 1.2, (10)*math.sqrt(3) )#1*math.sqrt(3)-0.2)

fig2 = cube(Vctr(20.,20.,30.), Vctr(0.,0.,1.), 0., 10.)

fig3 = box(Vctr(0.,0., 0.), Vctr(0.,0.,1), 0. , 10., 10., 10.)

e_fig1 = cube(Vctr(0., 0., 0.), Vctr(0.,0.,1.), 0., 20)
e_fig2 = spheroid(Vctr(0.,0., 10.), 10 * math.sqrt(2)*0.9)
e_fig3 = cylinder(Vctr(0.,0.,0.), Vctr(0., 0., 1.), 6, 20 )
e_fig4 = cylinder(Vctr(-10.,0.,10.), Vctr(1., 0., 0.), 6, 20 )
e_fig5 = cylinder(Vctr(0.,-11.,10.), Vctr(0., 1., 0.), 6, 21 )



M = Model()

trans0 = GlobalTrans(Vctr(1.,0.,0.), Vctr(0.,1.,0.), Vctr(0.,0.,1.))
trans1 = GlobalTrans(Vctr(1.,1.,0.)/math.sqrt(2), Vctr(-1.,1.,0.)/math.sqrt(2), Vctr(0.,0.,1.))

trans111 = GlobalTrans(math.sqrt(12)/12 *Vctr(2.0,-1.0,-1.0),
                        1./2            *Vctr(0.0,1.0,-1.0),
                        math.sqrt(6)/3  *Vctr(1.0,1.0,1.0))

transfcc4 = GlobalTrans(math.sqrt(12)/6 * Vctr( 1.0, -1.0, 0.0 ),
                                          Vctr( 1.0 , 1.0 , 0.0 ),
                        math.sqrt(6)/3  * Vctr( 1.0, 2.0, 3.0))



#--------------------------------------------------

# for i in range(100):
#     fig1 = Cylinder(Vctr(0.,0.,0.), 1, (i+1)*math.sqrt(3)-0.2)
#     M.init(fig1, trans111)
#     print (i+1)*math.sqrt(3)-0.2, M.total_cells(),M.used_cells()

# fig1 = Cylinder(Vctr(0.,0.,0.), 1.2, int(sys.argv[1])*math.sqrt(3))
# # M.init(fig1, trans111)
# M.init(fig1, transfcc4)
# print int(sys.argv[1])*math.sqrt(3), M.total_cells(), M.total_cells_x(), M.total_cells_y(), M.total_cells_z(), M.used_cells(), M.Natoms

# #:h total totalx totaly totalz used Natoms
# sys.exit(0)

# M.init(fig3-fig1, trans111) #!! куб с дыркой
M.init(e_fig1*e_fig2-(e_fig3+e_fig4+e_fig5), trans111)
# M.init(e_fig1*e_fig2-(e_fig3+e_fig4+e_fig5.move(Vctr(3.,0.,3.)).rotate(Vctr(3.,-11.,3.), Vctr(0.,0.,-0.2))), trans111)
# M.init(e_fig3+e_fig4+e_fig5, trans111)

# M.init(fig2, transfcc4)

M.border_space()
print "total cells:",M.total_cells();
print "used  cells:",M.used_cells();

M.Hext = Indx(0.,0.,1.)
M.alpha = 0.01
M.gamma = 0.1
M.h = 0.05 
M.T = 1
M.set_J(0,0,1.)

tcount = 10


M.simplestart(Vctr(1.,0.,0.))

S = Ofile("magnu_test/atoms.msh")
M.dump_head(S)
M.dump_data(S)

Stext = Ofile("magnu_test/diag.dat")
M.init_diag(Stext)
M.dump_diag(Stext)
for t in range(tcount):
    M.step()
    # M.stepRK4()
    print '\r',"%s / %s" %(t+1, tcount), ;sys.stdout.flush()
    M.dump_diag(Stext)
    M.dump_data(S)

#gplt -3d -U 'M1z(M1x,M1y)@:3' magnu_test/M1.dat -ur 0:pi -vr 0:2*pi -para=y -fn 'sin(u)*cos(v),sin(u)*sin(v),cos(u)' -raw 'set view equal' -raw 'set border 4095' -cu : { -k '' } -lbx '' -lby '' -lbz '' -xt.-fr ' ' -yt.-fr ' ' -zt.-fr ' ' -nk -to tM1.pdf showcmd=okular -pv=y

#gplt -3d -U 'M1z(M1x,M1y)' magnu_test/M1.dat -ur 0:pi -vr 0:2*pi -para=y -fn 'sin(u)*cos(v),sin(u)*sin(v),cos(u)' -raw 'set view equal'

# for i in `seq 1 100`; do python magnu_test.py $i >> fcc4_trans.dat; done
# gplt -U 'total(Natoms)' fcc4.dat -U 'total(Natoms)/4' fcc4_trans.dat