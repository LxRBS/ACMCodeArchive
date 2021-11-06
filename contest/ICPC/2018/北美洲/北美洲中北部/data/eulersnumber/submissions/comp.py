#!/usr/bin/python3

import sys
from decimal import *

getcontext().prec = 100

answer = Decimal(sys.argv[1])
expected = Decimal(sys.argv[2])

diff = abs(answer - expected)

if diff > Decimal(1e-12):
    sys.exit(1)

sys.exit(0)
