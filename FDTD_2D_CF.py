#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.cones import *

# ff = open("zz.log","w")
# sys.stderr = ff

Rx_width = 1
Lx_width_1 = 1
Lx_width_2 = 1
Ry_width = 1
Ly_width = 1
Nx = 50
Ny = 50
Sy = 24

def in_rec(indx, lb, rt):
    return (indx[0] >= lb[0]) and (indx[0] < rt[0]) and (indx[1] >= lb[1]) and (indx[1] < rt[1])

@statement
def start():
    Bx[0,0] = 0
    Bz[0,0] = 0
    Ey[0,0] = 0

@statement 
def calc_sec_LC(): 
    # Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,0] - Ey[0,-1])      
    # Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[0,0] - ifch(A * sin (Omega * time), Y==Sy,0))
    # Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,1] - Bx[0,0]) / dz - (Bz[1,0] - Bz[0,0]) / dx  )
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - ifch(A * sin (Omega * time), Y==Sy,0)) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
def in_sec_LC(indx): return in_rec(indx, (Lx_width_1,Ly_width), (Lx_width_1+Lx_width_2,Ny-Ry_width))

@statement
def calc_sec_BC():
    Bx[0,0] = 0
    Bz[0,0] = 0
    Ey[0,0] = 0
def in_sec_BC(indx): return in_rec(indx, (0,0), (Nx,Ny)) and (not in_rec(indx, (Lx_width_1,Ly_width), (Nx - Rx_width,Ny - Ry_width)))    

@statement
def calc_sec_CC(): 
    # Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,0] - Ey[0,-1])      
    # Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[0,0] - Ey[-1,0])
    # Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,1] - Bx[0,0]) / dz - (Bz[1,0] - Bz[0,0]) / dx  )
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - Bz[-1,0]) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
    
def in_sec_CC(indx):return in_rec(indx, (Lx_width_1+Lx_width_2,Ly_width), (Nx - Rx_width,Ny - Ry_width))


secCC = section(calc_sec_CC(),in_sec_CC,0)
secLC = section(calc_sec_LC(),in_sec_LC,1)
secBC = section(calc_sec_BC(),in_sec_BC,2)

sections = (secCC,secLC,secBC)
step_d=(1,1)

print "Start sections generating"

Myscheme = LRnLAscheme(sections, step_d)

top_base=[('Bx', 1, 1, 0),('Bz', 1, 1, 0)]
bottom_base=[('Ey', 1, 1, 0)]
# bottom_base=[('Bx', 1, 1, 0),('Bz', 1, 1, 0)]
# top_base=[('Ey', 1, 1, 0)]
t_count = 1
calc_cone_0 = cone2obj(Myscheme.top_bottom(bottom_base, top_base, t_count), Myscheme.acts, time = "time", h = "h")

top_base=[('Bx', 2, 1, 0),('Bz', 2, 1, 0)]
bottom_base=[('Ey', 2, 1, 0)]
# bottom_base=[('Bx', 2, 1, 0),('Bz', 2, 1, 0)]
# top_base=[('Ey', 2, 1, 0)]
t_count = 1
calc_cone_1 = cone2obj(Myscheme.top_bottom(bottom_base, top_base, t_count), Myscheme.acts, time = "time", h = "h")


print "Finish sections generating"

# sys.exit(0)
#-------------------------------Init model and calculations---------------------
mk_module("FDTD_2D_CF", globals())
from FDTD_2D_CF import *


M = Model()

M.data.init(Indx(Nx,Ny))

M.A = 1
M.Omega = 2
M.epsilon = 1
M.mu = 2
M.dx = 0.1
M.dy = 0.1
M.dz = 0.1
M.h = 0.05   # < 1/sqrt(1/dx**2 + 1/dy**2 + 1/dz**2)

 

print "Start init"
for i in range(Nx):
    for k in range(Ny):
        M.start(Indx(i,k))
print "Finish init"
print "Start calculations"


def calc(ii,kk,t):
    # print ii,kk,Indx(Nx-1-(ii-1),Ny-1-(kk-1))
    if Nx-1-(ii)==Lx_width_1: M.calc_cone_0(t*M.h,Indx(Nx-1-(ii+1),Ny-1-(kk+1)))
    else: M.calc_cone_1(t*M.h,Indx(Nx-1-(ii+2),Ny-1-(kk+1)))


for t in range(150):

    for i in range(Ny-Ry_width-Ly_width-1): 
        for k in range(i+1):
            # print Nx-Lx_width_1-Rx_width - i+k,k+1,t 
            calc(Nx-Lx_width_1-Rx_width - i+k,k+1,t)
    for i in range(Nx-Lx_width_1-Rx_width-Ny+Ry_width+Ly_width+1):
        for k in range(Ny-Ry_width-Ly_width):
            calc(Nx-Lx_width_1-Rx_width - (i+Ny-Ry_width-Ly_width-1)+k,k+1,t)
    for i in range(Ny-Ry_width-Ly_width-1):
        for k in range(Ny-Ry_width-Ly_width-1-i):
            calc(k+Lx_width_1,i+1+k+Ly_width,t)
    if t %5 == 0:
        fdata = open("res/EB2D_CF_%04d.dat"%t,"w")
        fdata.write("#:x y Ey Bx Bz\n")
        for k in range(Ny):
            for i in range(Nx):
                fdata.write("%s %s %f %f %f\n"%(i, k, M.data[Indx(i,k)].Ey, M.data[Indx(i,k)].Bx, M.data[Indx(i,k)].Bz))
            fdata.write("\n")
        fdata.close()    

    print '\r',t, ; sys.stdout.flush() 

print "Finish calculations"





# TODO 10.11.2014


#---------------------Done-----------------------
# E и B в одной ячейке
# гран условия - синус omega * t
# конусы получать смещение и время (инкрементировать каждый слой)
# иметь h - шаг по времени
# время - локальный для конусоида аргумент (асинхронность)
# старт и все смещения сделать через кроп аивлиба.
#динамическая размерность массива!!!!
#---------------------Done-----------------------

# сделать так, чтобы += учитывало зависимости. (collect deps натравливать на весь акт и проверять на +=, -=, ...)

# TODO 10.11.2014

# 1D обычные конусоиды дл максвелла ромбики, пирамидки, конефолды
# 2D максвелл конефолды и в 2D дифф - даймонды

# 2D максвелл - точечный источник на одной из границе
# дифф - дельта функция посредине.
