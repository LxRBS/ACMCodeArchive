#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
floating = integer + "(\.\d{1,10})?"
int3fl = re.compile(integer + "( " + floating + "){3}\n")

line = stdin.readline()
assert int3fl.match(line)

a = line.split()
n, p, s, v = int(a[0]), float(a[1]), float(a[2]), float(a[3])

assert 4 <= n <= 10 ** 6 and 0.001 <= p <= 5 * 10 ** 3 and 10 ** 6 <= s <= 10 ** 9 and 50 <= v <= 900

assert len(stdin.readline()) == 0
sys.exit(42)
