#!/usr/bin/python3

f=open("./e.txt","r")
g=open("./_e.txt","w")
f.read(2)
g.write("20")
c=str(f.read(98))
g.write(c)
while True:
    c = str(f.read(100))
    if not c or c == "" or len(c) == 0:
        break
    g.write(c)
f.close()
g.close()
