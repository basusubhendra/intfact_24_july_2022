#!/usr/bin/python3
import sys

f=open("./e.txt","r")
g=open("./_e.txt","w")
g.write("20")
f.read(2)
while True:
    c = str(f.read(1))
    g.write(str(c))
g.close()
f.close()
