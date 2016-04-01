# -*- encoding: utf-8 -*-
from __future__ import division, print_function
import visual
from visual import *
import math 
import numpy as np

E = np.eye(3)

sq2 = math.sqrt(2)
sq3 = math.sqrt(3)

def rotation(tx,ty,tz):
   Rx = np.array([[1,0,0], [0, cos(tx), -sin(tx)], [0, sin(tx), cos(tx)]])
   Ry = np.array([[cos(ty), 0, -sin(ty)], [0, 1, 0], [sin(ty), 0, cos(ty)]])
   Rz = np.array([[cos(tz), -sin(tz), 0], [sin(tz), cos(tz), 0], [0,0,1]])

   return np.dot(Rz, np.dot(Rx, Ry))

def axes(pos, A=E, new = False):
    mycolor = color.red if new else color.white
    arrow(pos = pos, axis = A.dot(np.array([1,0,0])), color=mycolor)
    arrow(pos = pos, axis = A.dot(np.array([0,1,0])), color=mycolor)
    arrow(pos = pos, axis = A.dot(np.array([0,0,1])), color=mycolor)

    label(pos = pos +A.dot(np.array([1,0,0])), text  = 'X'+new*"'", color=mycolor)
    label(pos = pos +A.dot(np.array([0,1,0])), text  = 'Y'+new*"'", color=mycolor)
    label(pos = pos +A.dot(np.array([0,0,1])), text  = 'Z'+new*"'", color=mycolor)

def mybox(pos, A=E,size=np.array([1,1,1])):

    box(pos=A.dot(pos)+A.dot(np.array([0.5,0.5,0.5])), axis = A.dot(np.array([size[0],0,0])), up = A.dot(np.array([0,1,0])), opacity = 0.1)

    cylinder(pos = A.dot(pos), axis = A.dot(np.array([1,0,0])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos), axis = A.dot(np.array([0,1,0])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos), axis = A.dot(np.array([0,0,1])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos+np.array([1,1,0])), axis = A.dot(np.array([-1,0,0])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos+np.array([1,1,0])), axis = A.dot(np.array([0,-1,0])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos+np.array([1,1,0])), axis = A.dot(np.array([0,0,1])), radius=0.01, color=color.black)
    
    cylinder(pos = A.dot(pos+np.array([1,0,1])), axis = A.dot(np.array([-1,0,0])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos+np.array([1,0,1])), axis = A.dot(np.array([0,1,0])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos+np.array([1,0,1])), axis = A.dot(np.array([0,0,-1])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos+np.array([0,1,1])), axis = A.dot(np.array([1,0,0])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos+np.array([0,1,1])), axis = A.dot(np.array([0,-1,0])), radius=0.01, color=color.black)
    cylinder(pos = A.dot(pos+np.array([0,1,1])), axis = A.dot(np.array([0,0,-1])), radius=0.01, color=color.black)


    


step = np.array([0.5,0.5,0.5])


scene.background = color.white
scene.width = 1000
scene.height = 800
rad = 0.05

colors = [color.magenta, color.red, color.blue, color.green]


parts = [np.array([0,0,0]),np.array([1,1,0]),np.array([1,0,1]),np.array([0,1,1])]
links = {0:[np.array([1,1,0]),np.array([-1,1,0]),np.array([1,-1,0]),np.array([-1,-1,0]),
            np.array([1,0,1]),np.array([-1,0,1]),np.array([1,0,-1]),np.array([-1,0,-1]),
            np.array([0,1,1]),np.array([0,-1,1]),np.array([0,1,-1]),np.array([0,-1,-1])
             ], 
        1:[np.array([1,1,0]), np.array([-1,1,0]),np.array([1,-1,0]),np.array([-1,-1,0]),
            np.array([0,1,1]),np.array([0,-1,1]),np.array([0,1,-1]),np.array([0,-1,-1]),
            np.array([1,0,1]),np.array([-1,0,1]),np.array([1,0,-1]),np.array([-1,0,-1]),
        ], 
        2:[np.array([1,1,0]), np.array([-1,1,0]),np.array([1,-1,0]),np.array([-1,-1,0]),
            np.array([0,1,1]),np.array([0,-1,1]),np.array([0,1,-1]),np.array([0,-1,-1]),
            np.array([1,0,1]),np.array([-1,0,1]),np.array([1,0,-1]),np.array([-1,0,-1]),
        ],
        3:[np.array([1,1,0]), np.array([-1,1,0]),np.array([1,-1,0]),np.array([-1,-1,0]),
            np.array([0,1,1]),np.array([0,-1,1]),np.array([0,1,-1]),np.array([0,-1,-1]),
            np.array([1,0,1]),np.array([-1,0,1]),np.array([1,0,-1]),np.array([-1,0,-1]),
        ]}

# for 


A = rotation(0.196*np.pi,np.pi/4,0)
# A = rotation(np.pi/4,np.pi/4,0)
# A =E
B = np.array(
    [[1,0.58,0],
    [0,1,0],
    [0,0,1]])
D = np.array(
    [[1.4,0,0],
    [0,1.64,0],
    [0,0,1.73]])
D1 = np.array(
    [[1,0,0],
    [0,1,0.670],#-0.335
    [0,0,1]])
D2 = np.array(
    [[1,0,0.33],
    [0,1,0],#-0.335
    [0,0,1]])
C = rotation(0.065*np.pi,0,0)
C=E;
axes(pos = np.array([-1,-1,-1]))
axes(pos = np.array([-1,-1,-1]), A=A, new=True)



Nx = 2
Ny = 2
Nz = 2

def boxes(Nx, Ny, Nz, size = np.array([1,1,1])):
    for i in range(-2,Nx):
        for k in range(-2,Ny):
            for j in range(Nz):
                mybox(pos=np.array([i,k,j]),size=size)

def onecell(pos, A=E, boxes=False ):
    if boxes: mybox(pos=pos, A=A)

    for i,p in enumerate(parts):
        sphere(radius=rad, pos = A.dot(p*step+pos), color = colors[i])
        for link in links[i]:
            cylinder(pos = A.dot(p*step+pos), axis = A.dot(link*step/2), radius=rad/10, color=colors[i])

def all(N, A=E, boxes = False):
    for s in range(N):
        onecell(np.array([s,s,s]), A=A, boxes=boxes)

        onecell(np.array([s-1,s,s]), A=A, boxes=boxes)
        onecell(np.array([s,s-1,s]), A=A, boxes=boxes)
        onecell(np.array([s,s,s-1]), A=A, boxes=boxes)

        onecell(np.array([s+1,s,s]), A=A, boxes=boxes)
        onecell(np.array([s,s+1,s]), A=A, boxes=boxes)
        onecell(np.array([s,s,s+1]), A=A, boxes=boxes)

        onecell(np.array([s-1,s+1,s-1]), A=A, boxes=boxes)
        onecell(np.array([s+1,s-1,s-1]), A=A, boxes=boxes)
        onecell(np.array([s-1,s-1,s+1]), A=A, boxes=boxes)

        onecell(np.array([s+1,s+1,s-1]), A=A, boxes=boxes)
        onecell(np.array([s+1,s-1,s+1]), A=A, boxes=boxes)
        onecell(np.array([s-1,s+1,s+1]), A=A, boxes=boxes)

        onecell(np.array([s+1,s-1,s]), A=A, boxes=boxes)
        onecell(np.array([s-1,s+1,s]), A=A, boxes=boxes)
        onecell(np.array([s+1,s,s-1]), A=A, boxes=boxes)
        onecell(np.array([s-1,s,s+1]), A=A, boxes=boxes)
        onecell(np.array([s,s+1,s-1]), A=A, boxes=boxes)
        onecell(np.array([s,s-1,s+1]), A=A, boxes=boxes)



#all()
# all(A=C.dot(B.dot(A)))


all(2, A=C.dot(D2.dot(D1.dot(D.dot(B.dot(A))))))

#all(8, A=E, boxes = False)

boxes(2,2,3,size=np.array([1,1,1]))

