#!/usr/bin/env python
from random import randint,shuffle
from sys import stdout

v = [randint(15, 150) for i in range(80000)]

def generate(l, r):
  for i in range(80000):
    stdout.write('sorted(')
  stdout.write('[')
  stdout.write(','.join(map(str, v[l:r])))
  stdout.write(']')
  for i in range(80000):
    stdout.write(')')

shuffle(v)
generate(0, len(v)) ; stdout.write('\n')
if randint(1, 2) == 1:
  v[randint(0, len(v) - 1)] += 1
  v[randint(0, len(v) - 1)] -= 1
shuffle(v)
generate(0, len(v)) ; stdout.write('\n')
