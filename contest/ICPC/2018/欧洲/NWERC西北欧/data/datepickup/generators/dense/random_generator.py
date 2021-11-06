#!/usr/bin/env python

import argparse
import random
import sys

SALT = '8f8hjj/dWs7GfZXkorLqDAEa'

MAX_N = 10**5
MAX_M = 10**5
MAX_B = 10**6

parser = argparse.ArgumentParser()
parser.add_argument('--name', '-f', help="test case name", type=str)
parser.add_argument('--vertices', '-n', help="number of vertices", type=int)
parser.add_argument('--edges', '-m', help="number of edges", type=int)
parser.add_argument('--max', '-x', help="maximum edge cost", type=int)
args = parser.parse_args(sys.argv[1:])

random.seed(SALT + (args.name if args.name else ''))
n = args.vertices if args.vertices is not None else random.randint(2, MAX_N)
m = args.edges if args.edges is not None else random.randint(0,MAX_M)
max_b = args.max if args.max is not None else MAX_B
assert 2 <= n <= MAX_N
assert 0 <= m <= MAX_M
assert 0 <= max_b <= MAX_B

sys.stderr.write('Generating case with n=%d\n' % (n))

while True:
    if m*4 >= n**2:
      es = [ (i,j,random.randint(1,max_b)) for i in range(n) for j in range(n) ]
      random.shuffle(es)
      es = es[:m]
    else:
      es = []
      done = set()
      while len(es) < m:
        i = random.randint(0, n-1)
        j = random.randint(0, n-1)
        if (i,j) not in done:
          es.append((i,j,random.randint(1,max_b)))
          done.add((i,j))

    adj = [ [] for i in range(n) ]
    for (u,v,t) in es:
        adj[u].append(v)

    ok = True
    for a in adj:
        if not a:
            ok = False
            break
    if not ok:
        continue

    vis = set()
    vis.add(0)
    S = [0]
    while S:
        u = S.pop()
        for v in adj[u]:
            if v in vis:
                continue
            vis.add(v)
            S.append(v)

    if n-1 not in vis:
        continue

    break

a = random.randint(0, max_b)
b = random.randint(0, max_b)
if a > b:
    a,b = b,a
sys.stdout.write('%d %d\n' % (a,b))
sys.stdout.write('%d %d\n' % (n,len(es)))
for (u,v,t) in es:
    sys.stdout.write('%d %d %d\n' % (u+1, v+1, t))

