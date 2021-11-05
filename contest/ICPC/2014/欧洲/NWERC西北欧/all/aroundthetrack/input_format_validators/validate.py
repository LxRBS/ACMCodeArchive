#!/usr/bin/python
from sys import stdin
import re
import sys

MAXC = 5000

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
twoint = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 3 <= n <= 50

for i in range(n):
    line = stdin.readline()
    assert twoint.match(line)
    a, b = list(map(int, line.split()))
    assert abs(a) <= MAXC and abs(b) <= MAXC

line = stdin.readline()
assert oneint.match(line)
m = int(line)
assert 3 <= m <= 50

for i in range(m):
    line = stdin.readline()
    assert twoint.match(line)
    a, b = list(map(int, line.split()))
    assert abs(a) <= MAXC and abs(b) <= MAXC

assert len(stdin.readline()) == 0
sys.exit(42)
