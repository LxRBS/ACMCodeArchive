#!/usr/bin/env python
import sys

s = raw_input()

if len(s) >= 3:
  e = s[-3:]
  if ('L' not in e and 'R' not in e) or ('U' not in e and 'D' not in e):
    print 'impossible'
    sys.exit(0)

(min_x, max_x, min_y, max_y) = (0, 0, 0, 0)
(x, y) = (0, 0)
blocks = set()
for m in s:
  if m == 'R':
    while x <= max_x+1 and (x+1, y) not in blocks: x += 1
    blocks.add((x+1, y))
  elif m == 'L':
    while x >= min_x-1 and (x-1, y) not in blocks: x -= 1
    blocks.add((x-1, y))
  elif m == 'U':
    while y <= max_y+1 and (x, y+1) not in blocks: y += 1
    blocks.add((x, y+1))
  else:
    while y >= min_y-1 and (x, y-1) not in blocks: y -= 1
    blocks.add((x, y-1))

  (min_y, max_y) = (min(min_y, y), max(max_y, y))
  (min_x, max_x) = (min(min_x, x), max(max_x, x))

print -x, -y
print len(blocks)
for i in blocks:
  print i[0]-x, i[1]-y
