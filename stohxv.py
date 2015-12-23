#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.stochastic import *

@statement
def start():
    X = X_start
    Vx = Vx_start

@statement
def calc():
    X +=  dt * .5 *Vx
    Vx += - dt * (a * X + b * X * X * X - alpha * M1X - A*sin(Omega * time) + gamma * Vx) + sqrt(2.*gamma*T*dt)*rand_gauss()
    X += dt * .5 *Vx

@statement
def means():
    M1X += X
    M2X += X*X
    M4X += X*X*X*X
    M1V += Vx
    M2V += Vx*Vx
    f[X, Vx] += 1



mk_module("Stoch_1D", globals())
from Stoch_1D import *

import aivlib.arrD1
import aivlib.arrD2
import math
import time


M = Model()



c_type = 0

# 0 - Обычный, одноямный, без внешней силы
# 1 - Обычный, одноямный, с внешней силой
# 2 - Обычный, двуямный, без внешней силы
# 3 - Обычный, двуямный, с внешней силой
# 4 - Сегнето, одноямный, без внешней силы
# 5 - Сегнето, одноямный, с внешней силой

M_a       = [1., 1., -1., -1., 1., 1.]
M_b       = [1., 1.,  1.,  1., 0.1, 0.1]
M_alpha   = [0., 0.,  0.,  0., 1.1, 1.1]
M_A       = [0., 0.1, 0., 0.1, 0., 0.01]
M_X_start = [1., 0. , 0.,  0., 1., 0.]
M_N = [5000, 5000, 200000, 5000, 30000, 5000]
T_ranges = [[0.7,1.0,1.3],
           [(i+1)/20. for i in range(40)],
           [0.1],
           [(i+1)/20. for i in range(40)],
           [(i+1)/80. for i in range(80)],
           [(i+1)/40. for i in range(40)]]

Omega_ranges = [[.5],
               [(i+1)/20. for i in range(40)],
               [.5],
               [(i+1)/20. for i in range(40)],
               [.5],
               [(i+1)/40. for i in range(40)]]


c_type_range = [2]

for c_type in c_type_range:
    M.partarr.init(Indx(M_N[c_type])) 
    M.f.init(Indx(400,400));M.f.min=Vctr(-2,-2);M.f.max=Vctr(2, 2);M.f.step = (M.f.max-M.f.min)/M.f.N
    M.a = M_a[c_type]; M.b = M_b[c_type]; M.gamma = 0.1; M.dt = 0.1; 
    M.Vx_start = 0.; M.X_start = M_X_start[c_type]
    M.A = M_A[c_type]; M.alpha = M_alpha[c_type];

    t1=5.0/M.gamma;

    if c_type%2 == 1:
        Ifile = open("Stoch_1D/dat/I_new_%s.dat"%(c_type),"w")
        print>>Ifile, "#:T Omega Ix Iy t1 t2 calc_time t_count"

    T_range = T_ranges[c_type]
    Omega_range = Omega_ranges[c_type]
    
    for M.T in T_range:
        for M.Omega in Omega_range:
            # if c_type%2 == 0:
            #     filemeans = open("Stoch_1D/dat/means_new_%s_%s_%s.dat"%(c_type,str(M.T).replace(".","_"),str(M.Omega).replace(".","_")),"w")
            #     print>>filemeans, "#:t M1X M2X M4X M1V M2V"  
            f_file = Ofile("Stoch_1D/dat/f%s.arr"%M.T)   
            t2 = t1 + 40*3.14/M.Omega
            Ix = 0.; Iy = 0.
            M.time = 0.
            M.start()
            start = time.time()
            while M.time < t2: 
                M.calc()
                M.means()
                M.f.dump(f_file)
                if c_type%2 == 1:
                    if M.time > t1:
                        Ix+=M.M1X * math.sin(M.Omega*M.time)
                        Iy+=M.M1X * math.cos(M.Omega*M.time)
                #if c_type%2 == 0:    
                    # print>>filemeans, " ".join(map(str,(M.time, M.M1X, M.M2X, M.M4X, M.M1V, M.M2V)))
            total = time.time()-start
            if c_type%2==1:
                print>>Ifile, "%s %s %s %s %s %s %s %s"%(M.T, M.Omega, Ix, Iy, t1,t2, total, M.time/M.dt)
            # I = 2*math.sqrt((Ix*M.dt)**2+(Iy*M.dt)**2)/(M.A*(t2-t1))
            print '\r', M.T, M.Omega, total; sys.stdout.flush()
        if c_type%2==1 :  print>>Ifile, ''

    #gplt -3d -U '2*0.05*sqrt(Ix**2+Iy**2)/(t2-t1)/0.1' I_T.dat
    #gplt -h3d -pm3d '' -U '(2*0.1*sqrt(Ix**2+Iy**2)/(t2-t1)/0.1)(T,Omega)' -lbz 'I' -sz sq I_1.dat -to preview=True I_1.pdf

#gplt -h3d -pm3d 'map' -U '(2*0.1*sqrt(Ix**2+Iy**2)/(t2-t1)/0.1)(T,Omega)' -rx 0.05:2 -ry 0.05:2 -lbz 'I' -sz sq I_1.dat -raw 'set contour' -raw 'set palette defined (0 "white", 1 "black")' -raw 'set cntrparam levels increment 0,0.5,6'

