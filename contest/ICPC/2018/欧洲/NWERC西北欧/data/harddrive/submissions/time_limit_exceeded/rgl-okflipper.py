#!/usr/bin/env python
from random import randint

n,e,b = map(int, raw_input().split())
b = set(map(int, raw_input().split()))

v = [int(i+1 not in b) for i in range(n)]
e -= sum([int(v[i] <> v[i+1]) for i in range(n-1)])
b = list(set(range(2,n+1)) - b)

if e % 2 == 1:
  v[0] = 0
  e += int(v[1] == 0) - int(v[1] == 1)

while e != 0:
  x = b[randint(0, len(b)-1)] - 1
  diff = 0
  if x > 0: diff += 2 * int(v[x] != v[x-1]) - 1
  if x < n-1: diff += 2 * int(v[x] != v[x+1]) - 1
  if diff * e <= 0:
    v[x] = 1 - v[x]
    e += diff

print ''.join(map(str, v))
