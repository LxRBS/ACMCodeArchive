#!/usr/bin/env python
import sys

n = int(raw_input())
v = map(int, raw_input().split())
j = v[0]
v = sorted([j-x for x in v[1:]])

av = v[0]
a = len(filter(lambda i: i==av, v))
b = len(filter(lambda i: i==av+1, v))

def iterate(a,b,av,it):
  if a == 1:
    a,b,av,it = (a+b, 0, av, it+1)
  else:
    a,b,av,it = (a/2, b+a-a/2, av-1, it+1)

  while a+b < len(v) and v[a+b] - it <= av + 1: b += 1
  return a,b,av,it

it = 0
while av >= 0: a,b,av,it = iterate(a,b,av,it)
print (it - 1)
