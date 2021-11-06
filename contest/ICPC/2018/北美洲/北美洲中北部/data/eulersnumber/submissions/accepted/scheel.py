#!/usr/bin/python3

import sys
import math
from decimal import *

getcontext().prec = 100

es = []
es.append(Decimal(1))

cutoff = 18

for i in range(1, cutoff):
    value = es[i-1]
    value += Decimal(1)/Decimal(math.factorial(i))
    es.append(value)

for i in range(cutoff, 10001):
    value = es[i-1]
    es.append(value)

line = int(sys.stdin.readline())
print(es[int(line)])
