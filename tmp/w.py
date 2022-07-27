#!/usr/bin/python3
f=open("./zero_indices.txt","r")
c=f.readlines()
d=c[::-1]
f.close()
k=open("./indices1.txt","w")
m=open("./indices2.txt","w")
for b in list(zip(c,d)):
    k.write(str(b[0].rstrip()) + "\n")
    m.write(str(b[1].rstrip()) + "\n")
k.close()
m.close()
