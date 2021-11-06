#!/usr/bin/env python
import sys

def log2(x): return max(1, x.bit_length()) - 1

n = int(raw_input())
v = map(int, raw_input().split())
v = sorted([v[0]-x for x in v[1:]])

av = v[0]
a = len(filter(lambda i: i==av, v))
b = len(filter(lambda i: i==av+1, v))

def iterate_single(a,b,av,it):
  return (a+b, 0, av, it+1) if a == 1 else (a/2, a+b-a/2, av-1, it+1)

def iterate_batch(a,b,av,it,reps=1):
  if reps == 0: return a,b,av,it
  steps = log2(a) + 1
  return a+b,0,av-(steps-1)*reps,it+steps*reps

def iterate_exactly(a,b,av,it,reps):
  if reps == 0: return a,b,av,it

  while reps > 0 and b > 0:
    a,b,av,it = iterate_single(a,b,av,it)
    reps -= 1

  period = log2(a+b) + 1
  a,b,av,it = iterate_batch(a,b,av,it,reps/period)
  reps %= period

  for i in range(reps):
    a,b,av,it = iterate_single(a,b,av,it)
  return a,b,av,it

it = 0
for ci in range(a+b,len(v) + 1):
  lef = -1
  for rad in range(55,-1,-1):
    mid = lef + (2 ** rad)
    a2,b2,av2,it2 = iterate_exactly(a,b,av,it,mid)
    if av2 >=0 and (ci == len(v) or v[ci] - it2 > av2+1):
      lef = mid
  a,b,av,it = iterate_exactly(a,b,av,it,lef+1)
  b += 1

print (it - 1)
