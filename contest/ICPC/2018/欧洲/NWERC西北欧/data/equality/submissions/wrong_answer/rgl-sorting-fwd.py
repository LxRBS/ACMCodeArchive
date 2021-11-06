#!/usr/bin/env python
import re

a,b = [re.findall('\w+|[()]', raw_input()) for line in (1,2)]

SORTED = 'sorted'
SHUFFLED = 'shuffle'
CONCAT = 'concat'

def match_brackets(a,s):
  depth = 0
  for i in range(s+1, len(a)):
    depth += (1 if a[i] == '(' else -1 if a[i] == ')' else 0)
    if depth == 0:
      return i
  assert False

def solve(a,shuffler):
  res = []
  j = 0
  for i in range(len(a)):
    if i >= j:
      if a[i] == SORTED or a[i] == SHUFFLED:
        j = match_brackets(a,i)
        fun = (sorted if a[i] == SORTED else shuffler)
        res += fun([int(x) for x in a[i:j] if x.isdigit()])
      elif a[i].isdigit():
        res.append(int(a[i]))
  return res

if solve(a,sorted) == solve(b,sorted):
  print 'equal'
else:
  print 'not equal'
