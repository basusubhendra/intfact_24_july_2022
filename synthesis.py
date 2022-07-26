#!/usr/bin/python3

import sys
from mpmath import *

f=open("./zero_indices.txt","r")
c=f.readlines()
f.close()
waveform = []
mp.prec = 256
mp.dps = 256
for line in c:
    l = str(line.rstrip())
    waveform.append(l)
print(waveform)
l = len(waveform)
for k in range(0, int(l / 2)):
    wave1=waveform[k]
    wave2=waveform[-(k+1)]
    z1 = str(zetazero(wave1).imag)
    z2 = str(zetazero(wave2).imag)
    print(z1, z2)

