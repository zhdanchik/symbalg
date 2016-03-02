#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.tiles import *

Nx = 10
Ny = 10 
Nz1 = 5
Nz2 = 5
def_type = "aiv::vctr<3,double>"

def in_rec(indx, lb, rt):
    return (indx[0] >= lb[0]) and (indx[0] < rt[0]) and (indx[1] >= lb[1]) and (indx[1] < rt[1])and (indx[2] >= lb[2]) and (indx[2] < rt[2])

@statement
def calc_sec1():
    H[0,0,0] = J*(m[-1,0,0]+m[1,0,0]+m[0,-1,0]+m[0,1,0]+m[0,0,-1]+m[0,0,1]) + H_ext
    m[0,0,0] = m[0,0,0] - h *( gamma*(m[0,0,0]%H[0,0,0])+alpha*(m[0,0,0]%(m[0,0,0]%H[0,0,0])))
    m[0,0,0] /= m[0,0,0].abs()
    m._type = def_type
    H._type = def_type
    H_ext._type = def_type
@statement
def start_sec1():
    H[0,0,0] = Vctr(0.,0.,0.)
    m[0,0,0] = m_init
    m._type = def_type
    H._type = def_type
    m_init._type = def_type
def in_sec1(indx): return in_rec(indx,(0,0,Nz1+1),(Nx,Ny,Nz1+Nz2)) 

@statement
def calc_sec2():
    H[0,0,0] = J*(m1[0,0,-1] + m1[-1,0,-1] + m1[0,-1,-1] + m1[-1,-1,-1] + m1[0,0,0] + m1[-1,0,0] + m1[0,-1,0] + m1[-1,-1,0]) + H_ext
    H1[0,0,0] = J*(m[0,0,0]+m[1,0,0]+m[0,0,1]+m[1,0,1]+m[0,1,0]+m[1,1,0]+m[0,1,1]+m[1,1,1]) + H_ext

    m[0,0,0] = m[0,0,0] - h *( gamma*(m[0,0,0]%H[0,0,0])+alpha*(m[0,0,0]%(m[0,0,0]%H[0,0,0])))
    m[0,0,0] /= m[0,0,0].abs()
    m1[0,0,0] = m1[0,0,0] - h *( gamma*(m1[0,0,0]%H1[0,0,0])+alpha*(m1[0,0,0]%(m1[0,0,0]%H1[0,0,0])))
    m1[0,0,0] /= m1[0,0,0].abs()
    m._type = def_type
    H._type = def_type
    m1._type = def_type
    H1._type = def_type
    H_ext._type = def_type
@statement
def start_sec2():
    H[0,0,0] = Vctr(0.,0.,0.)
    H1[0,0,0] = Vctr(0.,0.,0.)
    m[0,0,0] = m_init
    m1[0,0,0] = m1_init
    m._type = def_type
    H._type = def_type
    m_init._type = def_type
    m1._type = def_type
    H1._type = def_type
    m1_init._type = def_type
def in_sec2(indx): return in_rec(indx,(0,0,0),(Nx,Ny,Nz1)) 

@statement
def calc_sec3():
    H[0,0,0] = J*(m[-1,0,0]+m[1,0,0]+m[0,-1,0]+m[0,1,0]+m[0,0,1] + m1[0,0,-1] + m1[-1,0,-1] + m1[0,-1,-1] + m1[-1,-1,-1]) + H_ext
    m1[0,0,0] = 0
    m[0,0,0] = m[0,0,0] - h *( gamma*(m[0,0,0]%H[0,0,0])+alpha*(m[0,0,0]%(m[0,0,0]%H[0,0,0])))
    m[0,0,0] /= m[0,0,0].abs()
    m._type = def_type
    m1._type = def_type
    H._type = def_type
@statement
def start_sec3():
    H[0,0,0] = Vctr(0.,0.,0.)
    m[0,0,0] = m_init
    m._type = def_type
    H._type = def_type
    m_init._type = def_type
def in_sec3(indx): return in_rec(indx,(0,0,Nz1),(Nx,Ny,Nz1+1)) 


sections = (section(calc_sec1(),in_sec1,0),section(calc_sec2(),in_sec2,1),section(calc_sec3(),in_sec3,2))

step_d=(1,1,1)
Myscheme = scheme(sections, step_d)
t_count = 1
xs ,ys = [3,4], [3,4]

#-------------------------------
print "-------------------------------1-------------------------------"
zs = [2,3]

bottom_base = [('H', i,k,l, 0) for i in xs for k in ys for l in zs] + \
              [('H1', i,k,l, 0) for i in xs for k in ys for l in zs]             
top_base    = [('m', i,k,l, 0) for i in xs for k in ys for l in zs] + \
              [('m1', i,k,l, 0) for i in xs for k in ys for l in zs]
cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)

tmp_cone = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")(_conv = offset((-3,-3,-2)))
tile_1_calcH = filter_expr(tmp_cone,['H','H1'])
tile_1_calcm = filter_expr(tmp_cone,['m','m1'])

#cone2pdf(cone1,Myscheme.acts,"LL_magnet/sections/tmp1.pdf", "LR")

print tile_1_calcH
print tile_1_calcm

#sys.exit(0)
#Myscheme.diag()
#-------------------------------
print "-------------------------------2-------------------------------"
z1,z2 = 4,5
bottom_base = [('H', i,k,l, 0) for i in xs for k in ys for l in [z1,z2]] + \
              [('H1', i,k,l, 0) for i in xs for k in ys for l in [z1]]             
top_base    = [('m', i,k,l, 0) for i in xs for k in ys for l in [z1,z2]] + \
              [('m1', i,k,l, 0) for i in xs for k in ys for l in [z1]]

cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)

tmp_cone = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")(_conv = offset((-3,-3,-4)))
tile_2_calcH = filter_expr(tmp_cone,['H','H1'])
tile_2_calcm = filter_expr(tmp_cone,['m','m1'])
print tile_2_calcH
print tile_2_calcm
# cone2pdf(cone1,Myscheme.acts,"LL_magnet/sections/tmp2.pdf", "LR")
#sys.exit(0)
#-------------------------------

print "-------------------------------3-------------------------------"
zs = [6,7]
bottom_base = [('H', i,k,l, 0) for i in xs for k in ys for l in zs]
top_base    = [('m', i,k,l, 0) for i in xs for k in ys for l in zs]
cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
tmp_cone = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")(_conv = offset((-3,-3,-6)))
tile_3_calcH = filter_expr(tmp_cone,['H','H1'])
tile_3_calcm = filter_expr(tmp_cone,['m','m1'])
print tile_3_calcH
print tile_3_calcm
# cone2pdf(cone1,Myscheme.acts,"LL_magnet/sections/tmp.pdf", "LR")

#-------------------------------

BaseType = "aiv::vctr<3,double>"
Cells = [[("m",BaseType),("H",BaseType)],
         [("m",BaseType),("m1",BaseType),("H",BaseType),("H1",BaseType)]]

Tiles = [[("start",start_sec1()), ("step_H",tile_1_calcH), ("step_m",tile_1_calcm)],
         [("start",start_sec2()), ("step_H",tile_2_calcH), ("step_m",tile_2_calcm)],
         [("start",start_sec3()), ("step_H",tile_3_calcH), ("step_m",tile_3_calcm)]]

Geometry = {"gtype":"v", "Nx":Nx, "Ny":Ny, "Z":[0,]}

mk_module("LL_tiles", globals())



# Myscheme.diag()

# TODO
# нужно подумать над тем, как быть со связями "назад" 
# (т.е. если иди снизу то H на верхем слое не попадает, еслт t_count > 1 )