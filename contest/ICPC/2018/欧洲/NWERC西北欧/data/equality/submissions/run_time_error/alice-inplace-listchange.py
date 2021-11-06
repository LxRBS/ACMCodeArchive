#!/usr/bin/env python

def signature(l):
  def concat(a,b): return a.extend(b) or a
  def sorted(x): return x.sort() or x
  def shuffle(x): return x.sort() or x
  a = eval(l)
  def shuffle(x): return x.sort(reverse=True) or x
  b = eval(l)
  return a, b

if signature(raw_input()) == signature(raw_input()):
  print 'equal'
else:
  print 'not equal'
