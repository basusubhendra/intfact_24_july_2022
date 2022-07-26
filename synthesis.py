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
