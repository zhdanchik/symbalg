#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.cones import *

Rx_width = 1
Lx_width = 1
Ry_width = 1
Ly_width = 1
Nx = 20
Ny = 20
Sy = [9,10]


def in_rec(indx, lb, rt):
    return (indx[0] >= lb[0]) and (indx[0] < rt[0]) and (indx[1] >= lb[1]) and (indx[1] < rt[1])

@statement
def start():
    Ey[0,0] = 0
    Bx[0,0] = 0
    Bz[0,0] = 0

@statement
def start1():
    Ey[0,0] = 0
    Bx[0,0] = 0
    Bz[0,0] = 0

@statement
def calc_sec_LL(): 
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - 0) / dz - (Bz[0,0] - 0) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
def in_sec_LL(indx): return in_rec(indx, (0,0), (Lx_width,Ly_width))
@statement
def calc_sec_LC():
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - 0) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
def in_sec_LC(indx): return in_rec(indx, (0,Ly_width), (Lx_width,Ny - Ry_width)) and (indx[1]<Sy[0] or indx[1]>Sy[1])
@statement
def calc_sec_LC_s():
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - A * sin (Omega * time)) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
def in_sec_LC_s(indx): return in_rec(indx, (0,Ly_width), (Lx_width,Ny - Ry_width)) and indx[1]<=Sy[1] and indx[1]>=Sy[0]
@statement
def calc_sec_LR(): 
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - 0) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (0 - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
def in_sec_LR(indx): return in_rec(indx, (0,Ny - Ry_width), (Lx_width,Ny))
@statement
def calc_sec_CL(): 
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - 0) / dz - (Bz[0,0] - Bz[-1,0]) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
def in_sec_CL(indx):return in_rec(indx, (Lx_width,0), (Nx - Rx_width,Ly_width))
@statement
def calc_sec_CC(): 
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - Bz[-1,0]) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
def in_sec_CC(indx):return in_rec(indx, (Lx_width,Ly_width), (Nx - Rx_width,Ny - Ry_width))
@statement
def calc_sec_CR():
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - Bz[-1,0]) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (0 - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
def in_sec_CR(indx):return in_rec(indx, (Lx_width,Ny - Ry_width), (Nx - Rx_width,Ny))
@statement
def calc_sec_RL():
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - 0) / dz - (Bz[0,0] - Bz[-1,0]) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (0 - Ey[0,0])
def in_sec_RL(indx):return in_rec(indx, (Nx - Rx_width,0), (Nx,Ly_width))
@statement
def calc_sec_RC():
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - Bz[-1,0]) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (0 - Ey[0,0])
def in_sec_RC(indx):return in_rec(indx, (Nx - Rx_width,Ly_width), (Nx,Ny-Ry_width))
@statement
def calc_sec_RR():    
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - Bz[-1,0]) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (0 - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (0 - Ey[0,0])
def in_sec_RR(indx):return in_rec(indx, (Nx - Rx_width,Ny-Ry_width), (Nx,Ny))

secLL = section(calc_sec_LL(),in_sec_LL,0)
secLC = section(calc_sec_LC(),in_sec_LC,1)
secLC_s = section(calc_sec_LC_s(),in_sec_LC_s,2)
secLR = section(calc_sec_LR(),in_sec_LR,3)
secCL = section(calc_sec_CL(),in_sec_CL,4)
secCC = section(calc_sec_CC(),in_sec_CC,5)
secCR = section(calc_sec_CR(),in_sec_CR,6)
secRL = section(calc_sec_RL(),in_sec_RL,7)
secRC = section(calc_sec_RC(),in_sec_RC,8)
secRR = section(calc_sec_RR(),in_sec_RR,9)


sections = (secLL,secLC,secLC_s,secLR,secCL,secCC,secCR,secRL,secRC,secRR)
step_d=(1,1)

print "Start sections generating"

Myscheme = LRnLAscheme(sections, step_d)



d = 1

i_s = [1, 0, 0, 0, 1]
k_s = [1, 0, 0, 0, 1]

lxs = [ 0, 0, Rx_width, Nx-Lx_width-d, Nx-Lx_width-d ]
lys = [ 0, 0, Ry_width, Ny-Ly_width-d, Ny-Ly_width-d ]
rxs = [ ]

# t_count = 2*d-i-k+1

# bottom_base=[]
# top_base=[]
# k=1
# bottom_base.append(('Ey', Nx-Lx_width-d+k, Ny-Ly_width-d+k, 0))
# top_base.append(('Bx', Nx-Lx_width, Ny-Ly_width, 0))
# top_base.append(('Bz', Nx-Lx_width, Ny-Ly_width, 0))
# t_count = 2*(d-k)+1

# cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
# cone2pdf(cone1,Myscheme.acts,"LRnLA/sections/FDTD_2D_+2.pdf", "BT")
# calc_cone_3 = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")


# bottom_base=[]
# top_base=[]

# bottom_base.append(('Ey', Nx-Lx_width-d, Ny-Ly_width-d, 0))
# top_base.append(('Bx', Nx-Lx_width, Ny-Ly_width, 0))
# top_base.append(('Bz', Nx-Lx_width, Ny-Ly_width, 0))
# t_count = 2*d+1

# cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
# cone2pdf(cone1,Myscheme.acts,"LRnLA/sections/FDTD_2D_+1.pdf", "BT")
# calc_cone_2 = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")

# bottom_base=[]
# top_base=[]
# bottom_base.append(('Ey', Rx_width, Ry_width, 0))
# top_base.append(('Bx', Rx_width+d, Ry_width+d, 0))
# top_base.append(('Bz', Rx_width+d, Ry_width+d, 0))
# t_count = 2*d+1

# cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
# tmp_cone = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")
# cone2pdf(cone1,Myscheme.acts,"LRnLA/sections/FDTD_2D_1.pdf", "BT")
# calc_cone_1 = tmp_cone

# bottom_base=[]
# top_base=[]
# bottom_base.append(('Ey', 0, 0, 0))
# top_base.append(('Bx', d, d, 0))
# top_base.append(('Bz', d, d, 0))
# t_count = 2*d+1

# cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
# tmp_cone = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")
# cone2pdf(cone1,Myscheme.acts,"LRnLA/sections/FDTD_2D_0.pdf", "BT")
# calc_cone_0 = tmp_cone

# bottom_base=[]
# top_base=[]
# k=1
# bottom_base.append(('Ey', 0, 0, 0))
# top_base.append(('Bx', d-k, d-k, 0))
# top_base.append(('Bz', d-k, d-k, 0))
# t_count = 2*(d-k)+1

# cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
# tmp_cone = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")
# cone2pdf(cone1,Myscheme.acts,"LRnLA/sections/FDTD_2D_-1.pdf", "BT")
# calc_cone_m1 = tmp_cone

# sys.exit(1)

bottom_base=[]
top_base=[]
for i in range(Nx):
    for k in range(Ny):
        bottom_base.append(('Ey', i, k, 0))
        top_base.append(('Bx', i, k, 0))
        top_base.append(('Bz', i, k, 0))

t_count = 1

# cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
# tmp_cone = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")
# cone2pdf(cone1,Myscheme.acts,"LRnLA/sections/FDTD_2D_+2.pdf", "BT")
# calc_cone_all = tmp_cone


print "Finish sections generating"

# sys.exit(0)
#-------------------------------Init model and calculations---------------------
# mk_module("FDTD_2D", globals())
from FDTD_2D import *


M = Model()

M.data.init(Indx(Nx,Ny))

M.A = 1
M.Omega = 1
M.epsilon = 1
M.mu = 2
M.dx = 0.5
M.dy = 0.5
M.dz = 0.5
M.h = 0.2   # < 1/sqrt(1/dx**2 + 1/dy**2 + 1/dz**2)

 

print "Start init"
for i in range(Nx):
    for k in range(Ny):
        M.start(Indx(i,k))
print "Finish init"
print "Start calculations"



for t in range(100):
    M.calc_cone_all(t*M.h, Indx(0,0))
    fdata = open("res/EB2D_%04d.dat"%t,"w")
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
