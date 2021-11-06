#!/usr/bin/env python
from heapq import heappush, heappop

class LinkCut:
  def __init__(self):
    self.p = self.l = self.r = None

  def root(s):
    return s.p is None or s.p.l is not s and s.p.r is not s

  def rotl(s):
    if not s.root():
      if s.p.l is s:
        s.p.l = s.l
      else:
        s.p.r = s.l
    s.l.p = s.p ; s.p = s.l
    s.l = s.p.r ; s.p.r = s
    if s.l is not None:
      s.l.p = s

  def rotr(s):
    if not s.root():
      if s.p.l is s:
        s.p.l = s.r
      else:
        s.p.r = s.r
    s.r.p = s.p ; s.p = s.r
    s.r = s.p.l ; s.p.l = s
    if s.r is not None:
      s.r.p = s

  def rotate(s):
    if s.p.l is s: s.p.rotl()
    else: s.p.rotr()

  def splay(s):
    while not s.root():
      if not s.p.root():
        if (s.p.l is s) == (s.p.p.l is s.p):
          s.p.rotate()
        else:
          s.rotate()
      s.rotate()

  def link(s,x):
    s.expose()
    x.splay()
    s.p = x ; x.l = s
    s.expose()

  def cut(s):
    s.splay()
    if s.r is not None:
      s.r.p = s.p
      s.r = None
    s.p = None

  def expose(s):
    i = s ; j = None
    while i is not None:
      i.splay()
      i.l = j ; j = i ; i = i.p
    s.splay()

  def findroot(s):
    s.expose()
    x = s
    while x.r is not None:
      x = x.r
    x.expose()
    return x

def minimum_cost_arborescence(edge):
  n = len(edge)

  pi = [[] for i in range(n)]
  for i in range(n):
    pi[i] = sorted([(edge[j][i],j) for j in range(n) if i != j])

  lc = [LinkCut() for i in range(n)]
  p = [-1 for i in range(n)]
  exists = [True for i in range(n)]

  def get_pi(x):
    while not exists[pi[x][0][1]] or edge[pi[x][0][1]][x] != pi[x][0][0]:
      heappop(pi[x])
    return pi[x][0][1]

  res = 0
  for i in range(1,n):
    if not exists[i]:
      continue

    while lc[get_pi(i)].findroot() is lc[i]:
      j = get_pi(i)

      old_pi = {i: edge[j][i]}
      merging = set([i])
      x = j
      while x != i:
        exists[x] = False
        old_pi[x] = edge[p[x]][x]
        merging.add(x)
        x = p[x]

      res += old_pi[i]

      cycle_children = []
      for a in range(1, i):
        if exists[a] and p[a] in merging:
          cycle_children += [a]
          res -= edge[p[a]][a]
          lc[a].cut()

      for a in range(n):
        if exists[a] and a != i:
          edge[a][i] -= old_pi[i]

      changed = set()
      for b in merging:
        if b != i:
          for a in range(n):
            if a != i and exists[a]:
              edge[a][i] = min(edge[a][i], edge[a][b] - old_pi[b])
              if edge[b][a] < edge[i][a]:
                edge[i][a] = min(edge[i][a], edge[b][a])
                changed.add(a)

      pi[i] = []
      for a in range(n):
        if exists[a] and a != i:
          if a in changed:
            heappush(pi[a], (edge[i][a], i))
          pi[i] += [(edge[a][i], a)]
      pi[i].sort()

      for a in cycle_children:
        res += edge[i][a]
        lc[a].link(lc[i])
        p[a] = i

    lc[i].link(lc[get_pi(i)])
    res += edge[get_pi(i)][i]
    p[i] = get_pi(i)

  return res

def main():
  n = int(raw_input())

  edge = [[2**62 for i in range(n+1)] for j in range(n+1)]
  for i in range(1,n+1):
    arr = map(int, raw_input().split())
    arr[2 + arr[0]] = arr[1]
    for j,w in enumerate(arr[2:]):
      edge[j][i] = w

  print minimum_cost_arborescence(edge)

if __name__ == '__main__':
  main()
