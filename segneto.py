#!/usr/bin/python
from symbalg.skeletons.stochastic import *

@statement
def start():
    X = 1.
    Vx = 0.

@statement
def calc():
    X +=  dt * .5 *Vx
    Vx += - dt * (a * X + b * X * X * X -alpha * M1X- A*sin(Omega * time) + gamma * Vx) + sqrt(2.*gamma*T*dt)*rand_gauss()
    X += dt * .5 *Vx

@statement
def means():
    M1X += X
    M2X += X*X
    M4X += X*X*X*X
    M1V += Vx
    M2V += Vx*Vx
    f[X, Vx] += 1

mk_module('Segneto', globals())#, omp = True)

# from Segneto import *

# # import aivlib.arrD1
# # import aivlib.arrD2
# import math
# import time
# M = Model()

# M.partarr.init(Indx(5000)) 
# # M.M1Vx.init(Indx(50));M.M1Vx.min=Vctr(-10);M.M1Vx.max=Vctr(10);M.M1Vx.step = (M.M1Vx.max-M.M1Vx.min)/M.M1Vx.N
# # M.M2Vx.init(Indx(50));M.M2Vx.min=Vctr(-10);M.M2Vx.max=Vctr(10);M.M2Vx.step = (M.M2Vx.max-M.M2Vx.min)/M.M2Vx.N
# # M.f.init(Indx(100,100));M.f.min=Vctr(-2,-2);M.f.max=Vctr(2, 2);M.f.step = (M.f.max-M.f.min)/M.f.N

# M.a = 1; M.b = 1; M.gamma = 0.1; M.dt = 0.05; 
# M.aplha = 2; M.A = 0.1; t1=8.0/M.gamma; 


# Ifile = open("Segneto/I_T.dat","w")
# print>>Ifile, "#:T Omega Ix Iy t1 t2 calc_time t_count"
# for i in range(20):
#     for k in range(20):
#         M.T = (i+1)/10.
#         M.Omega = (k+1)/10.
#         t2=100*3.14/M.Omega
#         M.time = 0.
#         filemeans = open("Segneto/means/means_%s_%s.dat"%(i,k),"w")
#         #f_file = Ofile("Stoh_xv/means/f_%s.arr"%i)
#         # M1Vx_file = Ofile("Stoh_xv/M1Vx_file.arr")
#         # M2Vx_file = Ofile("Stoh_xv/M2Vx_file.arr")
#         Ix = 0.; Iy = 0.
#         M.start()
#         # print>>filemeans, "#:t M1X M2X M1V M2V"
#         start = time.time()
#         while M.time < t2: 
#             M.calc()
#             M.means()
#             if M.time > t1:
#                 Ix+=M.M1X * math.sin(M.Omega*M.time)
#                 Iy+=M.M1X * math.cos(M.Omega*M.time)
#             # M.f.dump(f_file)
#             # M.M1Vx.dump(M1Vx_file)
#             # M.M2Vx.dump(M2Vx_file)
#             print '\r', i, k, M.time, ; sys.stdout.flush()
#             # print>>filemeans, " ".join(map(str,(M.time, M.M1X, M.M2X, M.M1V, M.M2V)))
#         total = time.time()-start
#         print>>Ifile, "%s %s %s %s %s %s %s %s"%(M.T, M.Omega, Ix, Iy, t1,t2, total, M.time/M.dt)
#         # I = 2*math.sqrt((Ix*M.dt)**2+(Iy*M.dt)**2)/(M.A*(t2-t1))
#     print>>Ifile, ''
        
#gplt -3d -U '2*0.05*sqrt(Ix**2+Iy**2)/(t2-t1)/0.1' I_T.dat

from Segneto import *

import aivlib.arrD1
import aivlib.arrD2
import math
import time
M = Model()

M.partarr.init(Indx(5000)) 
# M.M1Vx.init(Indx(50));M.M1Vx.min=Vctr(-10);M.M1Vx.max=Vctr(10);M.M1Vx.step = (M.M1Vx.max-M.M1Vx.min)/M.M1Vx.N
# M.M2Vx.init(Indx(50));M.M2Vx.min=Vctr(-10);M.M2Vx.max=Vctr(10);M.M2Vx.step = (M.M2Vx.max-M.M2Vx.min)/M.M2Vx.N
M.f.init(Indx(100,100));M.f.min=Vctr(-2,-2);M.f.max=Vctr(2, 2);M.f.step = (M.f.max-M.f.min)/M.f.N

M.a = 1; M.b = 1; M.gamma = 0.1; M.dt = 0.05; 
M.alpha = 2; M.A = 0; t1=8.0/M.gamma; 


# Ifile = open("Segneto/I_T.dat","w")
# print>>Ifile, "#:T Omega Ix Iy t1 t2 calc_time t_count"
for i in range(20):
    # for k in range(20):
        M.T = (i+1)/10.
        M.Omega = 0#(k+1)/10.
        t2=300#100*3.14/M.Omega
        M.time = 0.
        filemeans = open("Segneto/means/means_%s.dat"%(i),"w")
        f_file = Ofile("Segneto/means/f_%s.arr"%i)
        # M1Vx_file = Ofile("Stoh_xv/M1Vx_file.arr")
        # M2Vx_file = Ofile("Stoh_xv/M2Vx_file.arr")
        Ix = 0.; Iy = 0.
        M.start()
        print>>filemeans, "#:t M1X M2X q M2V M4X"
        # start = time.time()
        while M.time < t2: 
            M.calc()
            M.means()
            # if M.time > t1:
            #     Ix+=M.M1X * math.sin(M.Omega*M.time)
            #     Iy+=M.M1X * math.cos(M.Omega*M.time)
            M.f.dump(f_file)
            # M.M1Vx.dump(M1Vx_file)
            # M.M2Vx.dump(M2Vx_file)
            print '\r', i, M.time, ; sys.stdout.flush()
            print>>filemeans, " ".join(map(str,(M.time, M.M1X, M.M2X, M.M1V, M.M2V, M.M4X)))
        # total = time.time()-start
        # print>>Ifile, "%s %s %s %s %s %s %s %s"%(M.T, M.Omega, Ix, Iy, t1,t2, total, M.time/M.dt)
        # I = 2*math.sqrt((Ix*M.dt)**2+(Iy*M.dt)**2)/(M.A*(t2-t1))
    # print>>Ifile, ''
        
