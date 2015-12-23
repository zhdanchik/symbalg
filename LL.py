#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.magnet import *

Nx = 3
Ny = 3
Nz = 3
def_type = "aiv::vctr<3>"
# Rx_width = 1
# Lx_width = 1
# Ry_width = 1
# Ly_width = 1
# Rz_width = 1
# Lz_width = 1

@statement
def start():
    H[0,0,0] = Vctr(0,0,0)
    m[0,0,0] = Init_m
    Init_m._type = def_type
    H._type = def_type
    m._type = def_type

@statement
def calc_sec_simple():
    H[0,0,0] = J*(m[-1,0,0]+m[1,0,0]+m[0,-1,0]+m[0,1,0]+m[0,0,-1]+m[0,0,1]) + H_ext
    m[0,0,0] = m[0,0,0] - h *( gamma*(m[0,0,0]%H[0,0,0])+alpha*(m[0,0,0]%(m[0,0,0]%H[0,0,0])))
    m[0,0,0] /= m[0,0,0].abs()
    H_ext._type = def_type

@statement
def calc_means():
    M1m+=m[0,0,0]
    M1m._type = def_type

def periodic_bc(size):
    def _per_bc(x):
        if isinstance(x,IndexOp):
            return x._a[tuple([x2+x1 if x1<0 else x1-x2 if x1>x2-1 else x1 for x1,x2 in zip(x._b,size)])]
        return x
    return _per_bc

in_rec = lambda indx, lb, rt : (indx[0] >= lb[0]) and (indx[0] < rt[0]) and (indx[1] >= lb[1]) and (indx[1] < rt[1])and (indx[2] >= lb[2]) and (indx[2] < rt[2])
in_sec = None
sections = []
for l in [0,1,Nz-1]:
    for k in [0,1,Ny-1]:
        for i in [0,1,Nx-1]:
            sec_calc = calc_sec_simple()(_conv=offset((i,k,l)))
            ii = (i,k,l); size = (Nx,Ny,Nz)
            in_sec = lambda indx,ii=ii, size=size: in_rec(indx, ii, tuple([i1+1 if i1!=1 else i2-1 for i1, i2 in zip(ii,size)]))
            # print [in_sec][0]((0,0,0)),i,k,l
            sections.append(section(sec_calc(_conv=periodic_bc((Nx,Ny,Nz))), in_sec, sections[-1].index+1 if sections else 0))




sections = tuple(sections)
step_d=(1,1,1)
print "Start sections generating"
Myscheme = scheme(sections, step_d)

bottom_base=[]
top_base=[]

for i in range(Nx): 
    for k in range(Ny): 
        for l in range(Nz):
            bottom_base.append(('m', i,k,l, 0))
            bottom_base.append(('m', i,k,l, 1))
            bottom_base.append(('H', i,k,l, 0))
            top_base.append(('m', i,k,l, 0))
            #top_base.append(('m', i,k,l, 1))

t_count = 1

cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
tmp_cone = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")
print tmp_cone
cone2pdf(cone1,Myscheme.acts,"LL_magnet/sections/tmp.pdf", "LR")
calc_cone_all = tmp_cone

mk_module("LL_magnet", globals())
