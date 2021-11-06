#!/usr/bin/env python

s,t = map(int,raw_input().split())
n,m = map(int,raw_input().split())

e = map(lambda i: map(int,raw_input().split()), range(m))

print 'digraph G {'
print '  rankdir=LR;'
print '  {rank=source; "%d"[label="start"   fontcolor="white" style="filled" fillcolor="black"];}' % (1)
print '  {             "%d"[label="%d...%d" fontcolor="white" style="filled" fillcolor="black"];}' % (n,s,t)
for i in e:
  print '  {} -> {} [label="{}"];'.format(*i)
print '}'
