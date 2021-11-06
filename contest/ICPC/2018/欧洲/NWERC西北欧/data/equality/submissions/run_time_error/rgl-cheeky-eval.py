#!/usr/bin/env python

def signature(l):
  def concat(a,b): return a + b
  def shuffle(x): return list(sorted(x))
  a = eval(l)
  def shuffle(x): return list(reversed(sorted(x)))
  b = eval(l)
  return a + b

if signature(raw_input()) == signature(raw_input()):
  print 'equal'
else:
  print 'not equal'
