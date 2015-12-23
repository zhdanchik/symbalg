import os

print ("#:T M1X")
for i in range(80):
    filemeans = open("new_dat/means_new_4_%s_0_5.dat"%(str((i+1)/80.).replace(".","_")),"r")
    av = 0.
    k=0
    for j,s in enumerate(filemeans.readlines()):
        if j>1500:
            av+= float(s.split(" ")[1])
            k+=1
    print (i+1)/80., av/k
