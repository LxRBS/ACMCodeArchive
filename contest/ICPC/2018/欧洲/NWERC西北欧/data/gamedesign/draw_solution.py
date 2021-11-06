#!/usr/bin/env python
import sys

if len(sys.argv) < 2:
  print 'Usage: ./solver [--latex] [--nocompress] < data.in | ' + sys.argv[0] + ' data.in'
  sys.exit(1)

do_compress = '--nocompress' not in sys.argv[1:]
do_latex = '--latex' in sys.argv[1:]
do_ascii = not do_latex

with open(sys.argv[-1]) as fin:
  moves = fin.read()[:-1]

print >>sys.stderr, 'moves={0}'.format(moves)

ball = tuple(map(int, raw_input().split()))
blocks = set(tuple(map(int, raw_input().split())) for i in range(int(raw_input())))
if do_compress:
  all_x = set(i[0] for i in list(blocks) + [(0,0), ball]); all_x |= set(i-1 for i in all_x) | set(i+1 for i in all_x)
  all_y = set(i[1] for i in list(blocks) + [(0,0), ball]); all_y |= set(i-1 for i in all_y) | set(i+1 for i in all_y)
  fix_x = dict((b,a) for a,b in enumerate(sorted(list(all_x))))
  fix_y = dict((b,a) for a,b in enumerate(sorted(list(all_y))))
  blocks = [(fix_x[x]-fix_x[0], fix_y[y]-fix_y[0]) for x,y in blocks]
  ball = (fix_x[ball[0]]-fix_x[0], fix_y[ball[1]]-fix_y[0])

min_x = min(i[0] for i in ([(0,0)] + list(blocks) + [ball]))
max_x = max(i[0] for i in ([(0,0)] + list(blocks) + [ball]))
min_y = min(i[1] for i in ([(0,0)] + list(blocks) + [ball]))
max_y = max(i[1] for i in ([(0,0)] + list(blocks) + [ball]))

def good(*ball):
  return tuple(ball) not in blocks and max(abs(ball[0]), abs(ball[1])) <= 10**9

def simulate_solution(ball):
  global blocks

  visits = 0
  ball = list(ball)
  vertices = [ball]
  for move in moves:
    if tuple(ball) == (0,0):
      print 'Ball reached centre too early.'
      sys.exit(43)

    if move == 'R':
      if (ball[0]+1, ball[1]) in blocks:
        print 'Trying to move through a wall'
        sys.exit(43)
      while good(ball[0]+1, ball[1]) and tuple(ball) != (0,0) and ball[0] < max_x:
        ball[0] += 1
        visits += int(tuple(ball) == (0,0))

    elif move == 'L':
      if (ball[0]-1, ball[1]) in blocks:
        print 'Trying to move through a wall'
        sys.exit(43)
      while good(ball[0]-1, ball[1]) and tuple(ball) != (0,0) and ball[0] > min_x:
        ball[0] -= 1
        visits += int(tuple(ball) == (0,0))

    elif move == 'U':
      if (ball[0], ball[1]+1) in blocks:
        print 'Trying to move through a wall'
        sys.exit(43)
      while good(ball[0], ball[1]+1) and tuple(ball) != (0,0) and ball[1] < max_y:
        ball[1] += 1
        visits += int(tuple(ball) == (0,0))

    elif move == 'D':
      if (ball[0], ball[1]-1) in blocks:
        print 'Trying to move through a wall'
        sys.exit(43)
      while good(ball[0], ball[1]-1) and tuple(ball) != (0,0) and ball[1] > min_y:
        ball[1] -= 1
        visits += int(tuple(ball) == (0,0))

    else:
      assert False, 'invalid move in input. move should be one of LRUD'

    vertices += [tuple(ball)]

  assert (visits == 1), 'ball should visit centre exactly once'
  assert ball[0] == 0 and ball[1] == 0
  return vertices

vertices = simulate_solution(ball)

if do_ascii:
  for y in range(max_y, min_y-1, -1):
    s = ''
    for x in range(min_x, max_x+1, +1):
      if (x, y) in blocks:
        assert (x, y) != ball
        assert (x, y) != (0, 0)
        s += '#'
      elif (x, y) == ball:
        assert (x, y) != (0, 0)
        s += 'O'
      elif (x, y) == (0, 0):
        s += 'x'
      else:
        s += ','
    print s

if do_latex:
  for x,y in blocks:
    print '\\block{{{0}}}{{{1}}}'.format(x,y)
  print '\\centre{{{0}}}{{{1}}}'.format(0,0)
  print '\\ball{{{0}}}{{{1}}}'.format(*ball)
