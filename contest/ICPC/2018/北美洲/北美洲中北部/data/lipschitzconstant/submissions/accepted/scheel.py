#!/usr/bin/python3

import sys
from decimal import *

N = int(sys.stdin.readline())
points = {}

getcontext().prec = 1000

for i in range(0, N):
    line = sys.stdin.readline()
    parts = line.split(" ")
    x = Decimal(parts[0].strip())
    y = Decimal(parts[1].strip())

    points[x] = y

sorted_xs = sorted(points.keys())
ans = 0

for i in range(1, len(sorted_xs)):
    x = sorted_xs[i-1]
    y = points[x]

    xx = sorted_xs[i]
    yy = points[xx]

    L = abs(yy - y) / abs(xx - x)
    ans = max(L, ans)

print(ans)
