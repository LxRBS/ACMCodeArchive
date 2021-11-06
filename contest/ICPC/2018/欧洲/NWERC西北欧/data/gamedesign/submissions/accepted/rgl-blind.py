#!/usr/bin/env python
import sys

def sign(x): return 1 if x>0 else -1 if x<0 else 0
def iof(x,y): return x.index(y) if y in x else -1
moves = raw_input()
occur = dict([(a,-1) for a in 'LRUD'] + [(a,i) for i,a in enumerate(moves)])

if len(moves) >= 3:
  ves = moves[-3:]
  if ('L' not in ves and 'R' not in ves) or ('U' not in ves and 'D' not in ves):
    print 'impossible'
    sys.exit(0)

vf = (moves[0] in 'UD')
vl = (moves[-1] in 'UD')
tm = 1
for a,b in zip(moves[:-1], moves[1:]):
  tm += int((a in 'UD')!=(b in 'UD'))
vm = (tm+int(    vf))/2
hm = (tm+int(not vf))/2

res = set()
y0 = 2 if vf else 4
x0 = 4 if vf else 2
for y in range(y0, y0+vm*4, +4):
  for x in range(-y, +y+1, +1):
    res.add((x,y)); res.add((x,-y))
for x in range(x0, x0+hm*4, +4):
  for y in range(-x, +x+1, +1):
    res.add((x,y)); res.add((-x,y))

x = (x0+hm*4-5)*sign(occur['R']-occur['L'])
y = (y0+vm*4-5)*sign(occur['U']-occur['D'])

print -x, -y
print len(res)
for a, b in res:
  print a-x, b-y
