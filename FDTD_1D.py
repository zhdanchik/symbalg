#!/usr/bin/python
# -*- encoding: utf-8 -*-

from symbalg.skeletons.cones import *

R_width = 1
L_width = 1
N = 50

@statement
def start():
    E[0] = 0
    B[0] = 0

@statement
def calc_sec_0():
    E[0] = E[0] + C0 * (B[0]-sin(Omega*time))
    B[0] = B[0] + C0 * (E[1]-E[0])
    # E[0] = E[0] + C0 * (B[1]-0)
    # B[1] = B[1] + C0 * (E[2]-E[0])
def in_sec_0(indx):
    return (indx[0] < L_width ) and (indx[0]>=0)

@statement
def calc_sec_1():
    E[0] = E[0] + C1 * (B[0]-B[-1])
    B[0] = B[0] + C1 * (E[1]-E[0])
    # E[0] = E[0] + C1 * (B[1]-B[-1])
    # B[1] = B[1] + C1 * (E[2]-E[0])
def in_sec_1(indx):
    return (indx[0] < N - R_width) and (indx[0]>=L_width)

@statement
def calc_sec_2():
    E[0] = E[0] + C2 * (B[0]-B[-1])
    B[0] = B[0] + C2 * (0-E[0])
    # E[0] = E[0] + C2 * (B[1]-B[-1])
    # B[1] = B[1] + C2 * (0-E[0])
def in_sec_2(indx):
    return (indx[0] <N ) and (indx[0]>=N - R_width)

sec0 = section(calc_sec_0(),in_sec_0,0)
sec1 = section(calc_sec_1(),in_sec_1,1)
sec2 = section(calc_sec_2(),in_sec_2,2)

sections = (sec0,sec1,sec2)
step_d=(1,)

Myscheme = LRnLAscheme(sections, step_d)

bottom_base = [('E', 0, 0)]
top_base = [('B', 0, 0), ('B', 1, 0), ('B', 2, 0), ('B', 3, 0)]

t_count = 4
cone1 = Myscheme.top_bottom(bottom_base, top_base, t_count)
calc_cone_1 = cone2obj(cone1, Myscheme.acts, time = "time", h = "h")
cone2pdf(cone1,Myscheme.acts,"LRnLA/sections/FDTD_1D_example4.pdf", "BT")

bottom_base=[]
top_base=[]
for i in range(N):
    bottom_base.append(('E', i, 0))
    top_base.append(('B', i, 0))
t_count = 1

calc_cone_1 = cone2obj(Myscheme.top_bottom(bottom_base, top_base, t_count), Myscheme.acts, time = "time", h = "h")
# cone2pdf(top_cone&bottom_cone,Myscheme.acts,"LRnLA/sections/FDTD_1D_1.pdf", "BT")




#-------------------------------Init model and calculations---------------------
mk_module("FDTD_1D", globals())
from FDTD_1D import *

M = Model()

M.data.init(Indx(N))
M.h = 0.01
M.Omega = 0.05
M.C0 = 0.1
M.C1 = 0.1
M.C2 = 0.1


for i in range(N):
    # M.start(Indx(i))
    M.data[Indx(i)].E=0
    M.data[Indx(i)].B=0

fdata = open("EB.dat","w")
fdata.write("#:x t E B\n")

for t in range(500):
    M.calc_cone_1(t, Indx(0))
    if t%5==0:
        for i in range(N):  
            fdata.write("%s %s %s %s\n"%(i, t*M.h, M.data[i].E, M.data[i].B))
        fdata.write('\n')

fdata.close()



# TODO 10.11.2014


#---------------------Done-----------------------
# E и B в одной ячейке
# гран условия - синус omega * t
# конусы получать смещение и время (инкрементировать каждый слой)
# иметь h - шаг по времени
# время - локальный для конусоида аргумент (асинхронность)
# старт и все смещения сделать через кроп аивлиба.
#---------------------Done-----------------------

# сделать так, чтобы += учитывало зависимости. (collect deps натравливать на весь акт и проверять на +=, -=, ...)


# TODO 10.11.2014

# 1D обычные конусоиды дл максвелла ромбики, пирамидки, конефолды
# 2D максвелл конефолды и в 2D дифф - даймонды

# 2D максвелл - точечный источник на одной из границе
# дифф - дельта функция посредине.