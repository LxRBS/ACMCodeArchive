#!/usr/bin/env python
from sys import stdin

line = stdin.readline()
a = line.split()

for i in range(1, 4):
    if a[i].find('.') != -1:
        c = a[i].find('.') + 11
        if c < len(a[i]):
            a[i] = a[i][:c]

print(" ".join(a))
