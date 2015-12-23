#!/usr/bin/python
# -*- encoding: utf-8 -*-

Nx = 3
Ny = 3
Nz = 3
#printf("%s\n",I.c_str());
from LL_magnet import *

M = Model()

M.data.init(Indx(Nx,Ny,Nz))

M.H_ext = Indx(1,0,0)
M.Init_m = Vctr(0,1,0)
M.alpha = 0.01
M.gamma = 0.1
M.J = 1
M.h = 0.05 

for i in range(Nx):
    for k in range(Ny):
        for l in range(Nz):
            M.start(Indx(i,k,l))
fdat = open("LL_magnet/data.dat","w")
M.calc_means()
fdat.write("#:t M1mx M1my M1mz\n")
fdat.write("%s %s\n"%(0, M.M1m))
for t in range(10000):
    M.calc_cone_all(t*M.h,Indx(0,0,0))
    M.calc_means()
    fdat.write("%s %s\n"%((t+1)*M.h, M.M1m))
    print '\r',t, ; sys.stdout.flush()

fdat.close()

#gplt -3d -U 'M1mz(M1mx,M1my)@:3' LL_magnet/data.dat -ur 0:pi -vr 0:2*pi -para=y -fn 'sin(u)*cos(v),sin(u)*sin(v),cos(u)' -raw 'set view equal' -raw 'set border 4095' -cu : { -k '' } -lbx '' -lby '' -lbz '' -xt.-fr ' ' -yt.-fr ' ' -zt.-fr ' ' -nk -to tM1.pdf showcmd=okular -pv=y

#gplt -3d -U 'M1mz(M1mx,M1my)' LL_magnet/data.dat -ur 0:pi -vr 0:2*pi -para=y -fn 'sin(u)*cos(v),sin(u)*sin(v),cos(u)' -raw 'set view equal'