#!/usr/bin/python3

import sys
from math import *

a = str(sys.argv[1])
b = str(sys.argv[2])
f=open("./pi.txt","r")
g=open("./e.txt","r")
pos = 0
hit = 0
while True:
    c = str(f.read(1))
    d = str(g.read(1))
    pos = pos + 1
    if c == a and d == b:
        hit = hit + 1
        if hit == ceil(16/3)*64:
            break
print(pos)
f.close()
g.close()
