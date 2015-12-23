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
    
def in_sec_CC(indx):return True#in_rec(indx, (Lx_width_1+Lx_width_2,Ly_width), (Nx - Rx_width,Ny - Ry_width))


secCC = section(calc_sec_CC(),in_sec_CC,0)
secLC = section(calc_sec_LC(),in_sec_LC,1)
secBC = section(calc_sec_BC(),in_sec_BC,2)

sections = (secCC,)#,secLC,secBC)
step_d=(1,1)

print "Start sections generating"

Myscheme = LRnLAscheme(sections, step_d)

top_base=[('Bx', 0, 0, 0),('Bz', 0, 0, 0)]
bottom_base=[('Ey', 0, 0, 0)]
# bottom_base=[('Bx', 1, 1, 0),('Bz', 1, 1, 0)]
# top_base=[('Ey', 1, 1, 0)]
t_count = 1

cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
cone2pdf(cone1,Myscheme.acts,"LRnLA/sections/FDTD_2D_CF_example.pdf", "BT")
calc_cone_0 = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")




#top_base=[('Bx', 2, 1, 0),('Bz', 2, 1, 0)]
#bottom_base=[('Ey', 2, 1, 0)]
# bottom_base=[('Bx', 2, 1, 0),('Bz', 2, 1, 0)]
# top_base=[('Ey', 2, 1, 0)]
#t_count = 1
#calc_cone_1 = cone2obj(Myscheme.top_bottom(bottom_base, top_base, t_count), Myscheme.acts, time = "time", h = "h")


