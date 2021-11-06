#!/usr/bin/env python

from os import system
from random import randint,shuffle,seed
from sys import stdout

seed('H5Er2JFAm2Dl/RFyVCku0sF7')

def gen(n):
  return sorted([randint(1, (10**9)-1) for i in range(n)])
  # return [i+1 for i in range(n)]

def go(v,w,shift,bits):
  chunks = [v[i:i+2] for i in range(0,len(v),2)]
  z = 0

  desc = '#'

  for i in range(len(chunks)):
    if i % 2 == shift:
      if bits % 2 == 1:
        chunks[i] = reversed(chunks[i])
        desc += 'b'
      else:
        desc += 'a'
      chunks[i] = 'shuffle([' + ','.join(map(str, chunks[i])) + '])'
    else:
      chunks[i] = '[' + ','.join(map(str,chunks[i])) + ']'
      desc += '-'
    desc += '#'

    # To stay in sync with the other row we consume
    # the bit regardless of whether we used it.
    bits /= 2

  w = '[' + ','.join(map(str, w)) + ']'
  chunks = [w] + [x for i,y in enumerate(chunks) for x in (y,w)]

  s = ''.join('concat(' + i + ',' for i in chunks[:-1]) + chunks[-1] + ')' * (len(chunks)-1)
  return s, desc

tc = 35
for spacelength in [1000, 1, 10]:
  for length in [4, 8]:
    for bits in range(2**(length/2)):
      finname = 'secret/%03d.in' % (tc)
      ansname = 'secret/%03d.ans' % (tc)
      descname = 'secret/%03d.desc' % (tc)
      tc += 1

      v = gen(length)
      w = gen(spacelength)
      (p0, p0s) = go(v,w,0,bits)
      (p1, p1s) = go(v,w,1,bits)

      with open(descname, 'w') as fdesc:
        fdesc.write('Alternating runs of shuffle([a,b]) and [a,b]\n')
        fdesc.write('Number of useful items each: ' + str(length) + '\n')
        fdesc.write('Number of useless items between each run: ' + str(spacelength) + '\n')
        fdesc.write('Pattern 0: ' + p0s + '\n')
        fdesc.write('Pattern 1: ' + p1s + '\n')

      with open(finname, 'w') as fin:
        fin.write(p0 + '\n')
        fin.write(p1 + '\n')
      system('pypy ../submissions/accepted/rgl-sorting.py <%s >%s' % (finname, ansname))
