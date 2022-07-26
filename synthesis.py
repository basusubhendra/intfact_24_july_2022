#!/usr/bin/python3

import sys

f=open("./zero_indices.txt","r")
c=f.readlines()
f.close()
waveform = []
for line in c:
    l = str(line.rstrip())
    waveform.append(l)
print(waveform)
l = len(waveform)
for k in range(0, int(l / 2)):
    wave1=waveform[k]
    wave2=waveform[-(k+1)]
    print(wave1, wave2)
