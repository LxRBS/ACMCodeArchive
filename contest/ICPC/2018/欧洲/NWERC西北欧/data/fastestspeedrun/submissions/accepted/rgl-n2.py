#!/usr/bin/env pypy

import sys
sys.setrecursionlimit(6000)

n = int(raw_input())
res = 0

cost = [[0 for i in range(n+1)] for j in range(n+1)]
active = [False for i in range(n+1)]
cycle = [False for i in range(n+1)]
root = [-1 if i > 0 else 0 for i in range(n+1)]
p = [0 for i in range(n+1)]

for i in range(1,n+1):
  arr = list(map(int, raw_input().split()))
  p[i] = arr[0]
  res += arr[1]
  for j in range(n+1):
    cost[j][i] = arr[j+2] - arr[1]

def dfs(x):
  if root[i] != -1:         pass
  if active[x]:             root[x] = x
  elif root[p[x]] != -1:    root[x] = root[p[x]]
  else:
    active[x] = True
    root[x] = dfs(p[x])
    if active[root[x]]:
      cycle[x] = True
    active[x] = False
  return root[x]

for i in range(n+1): root[i] = dfs(i)

for i in range(1,n+1):
  if root[i] == i:
    ring = [j for j in range(n+1) if root[j] == i and cycle[j]]
    rcost = min(cost[n][j] for j in ring)
    res += rcost
    for j in ring:
      for k in range(n+1):
        cost[k][j] -= rcost
      cost[i][j] = 0

for i in range(n+1):
  for j in range(n+1):
    if i == p[j] or cycle[i] and root[i] == root[j]:
      cost[i][j] = 0

visited = [False for i in range(n+1)]
for z in range(n+1):
  x = n+2
  for i in range(n+1):
    if not visited[i] and (x == n+2 or cost[0][i] < cost[0][x]):
      x = i
  visited[x] = True
  for i in range(n+1):
    cost[0][i] = min(cost[0][i], cost[0][x] + cost[x][i])

print(res + cost[0][n])
