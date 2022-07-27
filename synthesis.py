#!/usr/bin/python3

import sys
from mpmath import *

#synthesize num 
# from z1 using z2
def synthesize(z1, z2, num):
    pass

num = str(argv[1])
rnum = num[::-1]
l = len(num)
if l % 2 == 0:
    num = "0" + num
f=open("./zero_indices.txt","r")
c=f.readlines()
f.close()
waveform = []
mp.prec = 85
mp.dps = 85
_factor1 = ""
_factor2 = ""
for line in c:
    l = str(line.rstrip())
    waveform.append(l)
l = len(waveform)
for k in range(0, int(l / 2)):
    wave1=waveform[k]
    wave2=waveform[-(k+1)]
    z1 = str(zetazero(wave1).imag)
    z2 = str(zetazero(wave2).imag)
    print(z1, z2)
    factor1 = synthesize(z1, z2, num)
    factor2 = synthesize(z2, z1, num[::-1])
    _factor1 = _factor1 + factor1
    _factor2 = _factor2 + factor2
_factor2 = _factor2[::-1]
print(_factor1)
print(_factor2)
