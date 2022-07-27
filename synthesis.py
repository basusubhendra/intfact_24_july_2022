#!/usr/bin/python3

import sys
from mpmath import *

#synthesize num 
# from z1 using z2
def synthesize(z1, z2, n1, n2, rn1, rn2, t):
    if t == 0:
        print(n1, n2)
        print(rn2, rn1)
        print(z1)
        print(z2)
        print
        print
        input("Enter")
    elif t == 1:
        print(n2, n1)
        print(rn1, rn2)
        print(z1)
        print(z2)
        print
        print
        input("Enter")

num = str(sys.argv[1])
rnum = num[::-1]
l = len(num)
if l % 2 == 0:
    num = "0" + num
f=open("./zero_indices.txt","r")
c=f.readlines()
f.close()
waveform = []
mp.prec = 256
mp.dps = 256
_factor1 = ""
_factor2 = ""
for line in c:
    _l = str(line.rstrip())
    waveform.append(_l)
_l = len(waveform)
i = 0
t = 0
for k in range(0, int(_l / 2)):
    wave1=waveform[k]
    wave2=waveform[-(k+1)]
    z1 = str(zetazero(wave1).imag)
    z2 = str(zetazero(wave2).imag)
    z1 = z1.replace(".","0")
    z2 = z2.replace(".","0")
    n1 = num[i]
    n2 = num[i + 1]
    rn1 = rnum[i]
    rn2 = rnum[i + 1]
    factor1, factor2 = synthesize(z1, z2, n1, n2, rn1, rn2, t)
    t = 1 - t
    _factor1 = _factor1 + factor1
    _factor2 = _factor2 + factor2
    i = i + 1
_factor2 = _factor2[::-1]
print(_factor1)
print(_factor2)
