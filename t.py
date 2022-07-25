#!/usr/bin/python3

import sys

f=open("./zeros6","r")
g=open("./zeros.hpp","w")
g.write("int zeros[2001052] = { ")
c=f.readlines()
for line in c:
    l = str(line).rstrip().split(".")[0]
    g.write(str(l))
    if line != c[-1]:
        g.write(" , ")
g.write("};")
g.close()
f.close()
