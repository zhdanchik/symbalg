#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.cones import *

Rx_width = 1
Lx_width = 1
Ry_width = 1
Ly_width = 1
Nx = 20
Ny = 20

def in_rec(indx, lb, rt):
    return (indx[0] >= lb[0]) and (indx[0] < rt[0]) and (indx[1] >= lb[1]) and (indx[1] < rt[1])

@statement
def start():
    g[0,0] = 0
    f[0,0] = 0

@statement
def start_delta():
    g[0,0] = 0
    f[0,0] = 1./sqrt(dx**2 + dy**2)

@statement
def calc_sec_BC(): 
    g[0,0] = 0
    f[0,0] = 0

@statement
def calc_sec_CC(): 
    g[0,0] = f[0,0] + D * h *( (f[-1,0] - 2*f[0,0] + f[1,0]) / dx**2 + (f[0,-1] - 2*f[0,0] + f[0,1]) / dy**2 )
    f[0,0] = g[0,0]

def in_sec_CC(indx): return in_rec(indx, (Lx_width,Ly_width), (Nx - Rx_width,Ny - Ry_width))
def in_sec_BC(indx): return in_rec(indx, (0,0), (Nx,Ny)) and (not in_rec(indx, (Lx_width,Ly_width), (Nx - Rx_width,Ny - Ry_width)))

secBC = section(calc_sec_BC(),in_sec_BC,0)
secCC = section(calc_sec_CC(),in_sec_CC,1)

sections = (secBC,secCC)
step_d=(1, 1)

print "Start sections generating"

Myscheme = LRnLAscheme(sections, step_d)

bottom_base=[]
top_base=[]
for i in range(Nx):
    for k in range(Ny):
        bottom_base.append(('g', i, k, 0))
        top_base.append(('f', i, k, 0))
t_count = 1


cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
calc_cone_1 = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")

# cone2pdf(cone1,Myscheme.acts,"LRnLA/sections/FDTD_2D_1.pdf", "BT")

print "Finish sections generating"


#-------------------------------Init model and calculations---------------------
mk_module("Diff_2D", globals())
from Diff_2D import *


M = Model()

M.data.init(Indx(Nx,Ny))

M.Omega = 1
M.D = .1
M.dx = 0.5
M.dy = 0.5
M.h = 0.2   

print "Start init"
for i in range(Nx):
    for k in range(Ny):
        if i == int(Nx) / 2 and k == int(Ny) / 2:
            M.start_delta(Indx(i,k))
        else:
            M.start(Indx(i,k))
print "Finish init"
print "Start calculations"

for t in range(100):
    M.calc_cone_1(t*M.h, Indx(0,0))
    fdata = open("res/Diff2D_%04d.dat"%t,"w")
    fdata.write("#:x y f\n")
    for k in range(Ny):
        for i in range(Nx):
            fdata.write("%s %s %f\n"%(i, k, M.data[Indx(i,k)].f))
        fdata.write("\n")
    fdata.close()    

    print '\r',t, ; sys.stdout.flush() 


print "Finish calculations"
