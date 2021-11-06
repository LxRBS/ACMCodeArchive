#!/usr/bin/env python

import collections
import re
import sys

sys.setrecursionlimit(10**6)

class Type:
  LITERAL = 0
  SHUFFLED = 1
  SORTED = 2
  CONCAT = 3

class Function:
  def __init__(self, ftype, arr, min_val=None, max_val=None):
    if min_val is None: min_val = min(arr)
    if max_val is None: max_val = max(arr)

    self.ftype = ftype
    self.arr = arr
    self.min_val = min_val
    self.max_val = max_val

  # Return raw elements in any order.
  def flatten(self):
    return Function(Type.LITERAL, self.arr, self.min_val, self.max_val)

  def __repr__(self):
    if self.ftype == Type.LITERAL: desc = 'lit'
    if self.ftype == Type.SORTED: desc = 'sort'
    if self.ftype == Type.SHUFFLED: desc = 'fuzz'
    return '%s(%s)' % (desc, ','.join(map(str,self.arr)))

class Concatenation:
  def __init__(self, a, b):
    self.ftype = Type.CONCAT
    self.a = a
    self.b = b
    self.min_val = min(a.min_val, b.min_val)
    self.max_val = max(a.max_val, b.max_val)

  # Return raw elements in any order.
  def flatten(self):
    todo = [self]
    items = []
    while len(todo) > 0:
      x = todo.pop()
      if x.ftype == Type.CONCAT:
        todo += [x.b, x.a]
      else:
        items += [x.flatten().arr]
        x.arr = None

    arr = items[0]
    for i in range(1,len(items)):
      items[i].extendleft(reversed(arr))
      arr, items[i] = items[i], None
    return Function(Type.LITERAL, arr, self.min_val, self.max_val)

  def __repr__(self):
    return 'cat(%s,%s)' % (self.a, self.b)

def f_literal(a):
  return Function(Type.LITERAL, a)

def f_shuffled(a):
  a = a.flatten()
  if len(a.arr) == 1 or a.min_val == a.max_val:
    return a
  else:
    return Function(Type.SHUFFLED, a.arr, a.min_val, a.max_val)

def f_sorted(a):
  a = a.flatten()
  if len(a.arr) == 1 or a.min_val == a.max_val:
    return a
  else:
    return Function(Type.SORTED, a.arr, a.min_val, a.max_val)

def f_concat(a, b):
  return Concatenation(a, b)

def append_to_list(x, res):
  if len(res) > 0 and res[-1].ftype == Type.LITERAL and x.ftype == Type.LITERAL:
    res[-1] = Concatenation(res[-1], x).flatten()
  else:
    res.append(x)

def to_list(x, res, care=True):
  to_list_todo = [(x, res)]
  while len(to_list_todo) > 0:
    x, res = to_list_todo.pop()
    if x.ftype == Type.CONCAT:
      to_list_todo += [(x.b, res)]
      to_list_todo += [(x.a, res)]
    elif x.ftype == Type.SHUFFLED and care:
      append_to_list(Function(Type.SHUFFLED, collections.deque(sorted(x.arr))), res)
    elif x.ftype == Type.SORTED and care:
      append_to_list(Function(Type.LITERAL, collections.deque(sorted(x.arr))), res)
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
  if False:
    print >>sys.stderr, res
  return res

a = parse_fn(raw_input())
b = parse_fn(raw_input())
if str(a) == str(b):
  print 'equal'
else:
  print 'not equal'
