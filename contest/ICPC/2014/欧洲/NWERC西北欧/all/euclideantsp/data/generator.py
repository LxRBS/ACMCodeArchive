#!/usr/bin/env python3
import random
from sys import stdin

s = stdin.readline().strip().split()
if s[0] == "exactly":
    n = int(s[1])
else:
    n = random.randint(int(s[1]), int(s[2]))

s = random.uniform(1e6, 1e9)
p = random.uniform(1, 5000)
v = random.uniform(50, 900)

print(n, p, s, v)
