#!/usr/bin/env python
from random import randint
from sys import stdout

v = [randint(2, 10**6) for i in range(20)]

def generate(l, r):
  if r - l <= 4:
    stdout.write('[')
    stdout.write(','.join(map(str, v[l:r])))
    stdout.write(']')
  else:
    stdout.write('concat(')
    mid = randint(l + 2, (l + r) / 2)
    generate(l, mid)
    stdout.write(',')
    generate(mid, r)
    stdout.write(')')

generate(0, len(v)) ; stdout.write('\n')
if randint(1, 2) == 1:
  v[randint(0, len(v) - 1)] += 1
  v[randint(0, len(v) - 1)] -= 1
generate(0, len(v)) ; stdout.write('\n')
