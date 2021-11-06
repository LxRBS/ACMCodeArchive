#!/usr/bin/env python

import collections
import re
import sys

#
# TODO: this solution is slightly bugged, in that it will not treat
# arrays of identical values properly. These need to be squashed into
# a LITERAL no matter what.
#

class FunctionType:
  LITERAL = 0
  SHUFFLED = 1
  SORTED = 2
  CONCAT = 3

def compare(a, b):
  if a[0] <> b[0]:
    return

def f_literal(a):
  return (FunctionType.LITERAL, a)

def f_shuffled(a):
  a = flatten(a)
  if len(a[1]) == 1:
    return f_literal(a[1])
  else:
    return (FunctionType.SHUFFLED, a[1])

def f_sorted(a):
  a = flatten(a)
  if len(a[1]) == 1:
    return f_literal(a[1])
  else:
    return (FunctionType.SORTED, a[1])

def f_concat(a, b):
  return (FunctionType.CONCAT, a, b)

def flatten(x):
  if x[0] == FunctionType.LITERAL:
    return x
  elif x[0] == FunctionType.CONCAT:
    a = flatten(x[1])[1]
    b = flatten(x[2])[1]
    if len(a) < len(b):
      b.extendleft(reversed(a))
      return (FunctionType.LITERAL, b)
    else:
      a.extend(b)
      return (FunctionType.LITERAL, a)
  else:
    return f_literal(x[1])

def append_to_list(x, res):
  if len(res) > 0 and res[-1][0] == FunctionType.LITERAL and x[0] == FunctionType.LITERAL:
    a = res[-1][1]
    b = x[1]
    if len(a) < len(b):
      b.extendleft(reversed(a))
      res[-1] = f_literal(b)
    else:
      a.extend(b)
      res[-1] = f_literal(a)
  else:
    res.append(x)

def to_list(x, res):
  if x[0] == FunctionType.CONCAT:
    to_list(x[1], res)
    to_list(x[2], res)
  elif x[0] == FunctionType.SHUFFLED:
    append_to_list(f_shuffled(f_literal(sorted(x[1]))), res)
  elif x[0] == FunctionType.SORTED:
    append_to_list(f_literal(sorted(x[1])), res)
  else:
    append_to_list(x, res)

def parse_fn(s):
  stack = []
  for i in reversed(re.findall('\w+\(|\[[^\]]+]', s)):
    if i == 'shuffle(':
      a = stack.pop()
      stack.append(f_shuffled(a))
    elif i == 'sorted(':
      a = stack.pop()
      stack.append(f_sorted(a))
    elif i == 'concat(':
      a = stack.pop()
      b = stack.pop()
      stack.append(f_concat(a, b))
    elif re.match('^\[\d+(,\d+)*]$', i):
      stack.append(f_literal(collections.deque(map(int, re.findall('\d+', i)))))
    else:
      print 'Invalid token', i
      sys.exit(1)

  res = []
  to_list(stack.pop(), res)
  print >>sys.stderr, res
  return res

a = parse_fn(raw_input())
b = parse_fn(raw_input())
if tuple(a) == tuple(b):
  print 'equal'
else:
  print 'not equal'
