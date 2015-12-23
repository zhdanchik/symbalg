file1 = open("new_dat/I_new_5.dat","r")
av = 0.
k=0
for j,s in enumerate(file1.readlines()):
    if j >0 :
        if len(s)>1:
            av+= float(s.split(" ")[6])/float(s.split(" ")[7])/5000.*1.1e9
            k+=1
print av/k