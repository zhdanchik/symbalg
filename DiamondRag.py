#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.cones import *


Rx_width = 1
Lx_width_1 = 1
Lx_width_2 = 1
Ry_width = 1
Ly_width = 1
Nx = 50
Ny = 50

def in_rec(indx, lb, rt):
    return (indx[0] >= lb[0]) and (indx[0] < rt[0]) and (indx[1] >= lb[1]) and (indx[1] < rt[1])


@statement
def calc_sec_CC():
    Tz[0,0] = Tz[0,0] + h*mu3*((Vy[1,0] - Vy[0,0])/dx + (Vx[0,0] - Vx[0,-1])/dy)
    # Tx[0,0] = Tx[0,0] + h*mu1*((Vz[0,0] - Vz[0,-1])/dy + 0)
    Sx[0,0] = Sx[0,0] + h*(l1 * (Vx[0,0] - Vx[-1,0])/dx + lambda2 * (Vy[0,1] - Vy[0,0])/dy + 0)
    Sy[0,0] = Sy[0,0] + h*(l2 * (Vy[0,1] - Vy[0,0])/dy + 0 + lambda1 * (Vx[0,0] - Vx[-1,0])/dx)
    # Sz[0,0] = Sz[0,0] + h*(0 + lambda1 * (Vx[0,0] - Vx[-1,0])/dx + lambda2 * (Vy[0,1] - Vy[0,0])/dy)
    # Ty[0,0] = Ty[0,0] + h*mu2*(0 + (Vz[0,0] - Vz[-1,0])/dx)
    Vx[0,0] = Vx[0,0] + (h/rho) * ((Sx[1,0] - Sx[0,0])/dx + (Tz[0,1]-Tz[0,0])/dy + 0) 
    # Vz[0,0] = Vz[0,0] + (h/rho) * (0 + (Ty[1,0]-Ty[0,0])/dx + (Tx[0,1]-Tx[0,0])/dy)
    Vy[0,0] = Vy[0,0] + (h/rho) * ((Sy[0,0] - Sy[0,-1])/dy + 0 + (Tz[0,0]-Tz[-1,0])/dx )  
def in_sec_CC(indx):return in_rec(indx, (Lx_width_1+Lx_width_2,Ly_width), (Nx - Rx_width,Ny - Ry_width))

@statement
def calc_sec_BC():
    Tz[0,0] = 0
    # Tx[0,0] = 0
    Sx[0,0] = 0
    Sy[0,0] = 0
    # Sz[0,0] = 0
    # Ty[0,0] = 0
    Vx[0,0] = 0
    # Vz[0,0] = 0
    Vy[0,0] = 0
def in_sec_BC(indx): return in_rec(indx, (0,0), (Nx,Ny)) and (not in_rec(indx, (Lx_width_1,Ly_width), (Nx - Rx_width,Ny - Ry_width)))    

@statement
def start():
    Tz[0,0] = 0
    # Tx[0,0] = 0
    Sx[0,0] = 0
    Sy[0,0] = 0
    # Sz[0,0] = 0
    # Ty[0,0] = 0
    Vx[0,0] = 0
    # Vz[0,0] = 0
    Vy[0,0] = 0

@statement
def calc_sec_LC():
    # Vx[-1,0] = A * sin (Omega * time)
    # Vz[-1,0], Tz[-1,0] = 0, 0 ???
    Tz[0,0] = Tz[0,0] + h*mu3*((Vy[1,0] - Vy[0,0])/dx + (Vx[0,0] - Vx[0,-1])/dy)
    # Tx[0,0] = Tx[0,0] + h*mu1*((Vz[0,0] - Vz[0,-1])/dy + 0)
    Sx[0,0] = Sx[0,0] + h*(l1 * (Vx[0,0] - A * sin (Omega * time))/dx + lambda2 * (Vy[0,1] - Vy[0,0])/dy + 0)
    Sy[0,0] = Sy[0,0] + h*(l2 * (Vy[0,1] - Vy[0,0])/dy + 0 + lambda1 * (Vx[0,0] - A * sin (Omega * time))/dx)
    # Sz[0,0] = Sz[0,0] + h*(0 + lambda1 * (Vx[0,0] - A * sin (Omega * time))/dx + lambda1 * (Vy[0,1] - Vy[0,0])/dy)
    # Ty[0,0] = Ty[0,0] + h*mu2*(0 + (Vz[0,0] - 0)/dx)
    Vx[0,0] = Vx[0,0] + (h/rho) * ((Sx[1,0] - Sx[0,0])/dx + (Tz[0,1]-Tz[0,0])/dy + 0) 
    # Vz[0,0] = Vz[0,0] + (h/rho) * (0 + (Ty[1,0]-Ty[0,0])/dx + (Tx[0,1]-Tx[0,0])/dy)
    Vy[0,0] = Vy[0,0] + (h/rho) * ((Sy[0,0] - Sy[0,-1])/dy + 0 + (Tz[0,0]-0)/dx )  

def in_sec_LC(indx): return in_rec(indx, (Lx_width_1,Ly_width), (Lx_width_1+Lx_width_2,Ny-Ry_width))

secCC = section(calc_sec_CC(),in_sec_CC,0)
secLC = section(calc_sec_LC(),in_sec_LC,1)
secBC = section(calc_sec_BC(),in_sec_BC,2)

sections = (secCC,secLC,secBC)
step_d=(1,1)

print "Start sections generating"

Myscheme = LRnLAscheme(sections, step_d)

# top_base=[('Vx', 1, 1, 0),('Vy', 1, 1, 0),('Vz', 1, 1, 0)]
# bottom_base=[('Tx', 1, 1, 0),('Ty', 1, 1, 0),('Tz', 1, 1, 0)]
# t_count = 1
# calc_cone_0 = cone2obj(Myscheme.top_bottom(bottom_base, top_base, t_count), Myscheme.acts, time = "time", h = "h")
    


top_base=[('Vx', 2, 1, 0),('Vy', 2, 1, 0),('Sx', 2, 1, 0),('Sy', 2, 1, 0)]
bottom_base=[('Tz', 2, 1, 0),('Sx', 2, 1, 0),('Sy', 2, 1, 0)]
# bottom_base=[('Tx', 2, 1, 0),('Ty', 2, 1, 0),('Tz', 2, 1, 0)]#,('Sx', 2, 1, 0),('Sy', 2, 1, 0),('Sz', 2, 1, 0)]
t_count = 1

cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
cone2pdf(cone1,Myscheme.acts,"LRnLA/DR/DR_0.pdf", "LR")
calc_cone_1 = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")

