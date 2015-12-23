import symbalg
from symbalg import *
from symbalg.statements import *
from symbalg.expressions import *
from symbalg.cone_funcs import *

@statement
def calc_sec_test():
    Ey[0,0] = Ey[0,0] + (h/epsilon) *( (Bx[0,0] - Bx[0,-1]) / dz - (Bz[0,0] - Bz[-1,0]) / dx  )
    Bx[0,0] = Bx[0,0] + (h / (mu * dz)) * (Ey[0,1] - Ey[0,0])      
    Bz[0,0] = Bz[0,0] - (h / (mu * dx)) * (Ey[1,0] - Ey[0,0])
def in_sec_test(indx): return True

sectest = section(calc_sec_test(),in_sec_test,0)
sections = (sectest,)
step_d=(1,1)

Myscheme = LRnLAscheme(sections, step_d)

bottom_base=[('Ey', 0, 0, 0)]
top_base=[('Bx', 1, 1, 0),('Bz', 1, 1, 0)]

t_count = 1
plp1 = cone2list(Myscheme.bottom_cone(bottom_base, t_count), Myscheme.acts)
plm1 = cone2list(Myscheme.top_cone(top_base, t_count), Myscheme.acts)

t_count = 2
plp2 = cone2list(Myscheme.bottom_cone(bottom_base, t_count), Myscheme.acts)
plm2 = cone2list(Myscheme.top_cone(top_base, t_count), Myscheme.acts)


ifdeps=False

s0 = get_square(calc_sec_test(), ifdeps = ifdeps)
r0 =  get_rmb(calc_sec_test(), ifdeps = ifdeps)

print "---------------------------------"
print "sq  = ", s0,"; S_sq = ", S_sq(s0)  
print "rmb = ", r0, "; S_rmb = ", S_rmb(r0)


sp1 = get_square(plp1, ifdeps = ifdeps)
rp1 = get_rmb(plp1, ifdeps = ifdeps )
sm1 = get_square(plm1, ifdeps = ifdeps)
rm1 = get_rmb(plm1, ifdeps = ifdeps )

print "--------------m/p-1--------------"
print "sq  = ", sp1,"; S_sq = ", S_sq(sp1) 
print "rmb = ", rp1, "; S_rmb = ", S_rmb(rp1)
print "sq  = ", sm1,"; S_sq = ", S_sq(sm1) 
print "rmb = ", rm1, "; S_rmb = ", S_rmb(rm1)

sp2 = get_square(plp2, ifdeps = ifdeps)
rp2 = get_rmb(plp2, ifdeps = ifdeps )
sm2 = get_square(plm2, ifdeps = ifdeps)
rm2 = get_rmb(plm2, ifdeps = ifdeps )

print "--------------m/p-2--------------"
print "sq  = ", sp2,"; S_sq = ", S_sq(sp2) 
print "rmb = ", rp2, "; S_rmb = ", S_rmb(rp2)
print "sq  = ", sm2,"; S_sq = ", S_sq(sm2) 
print "rmb = ", rm2, "; S_rmb = ", S_rmb(rm2)

