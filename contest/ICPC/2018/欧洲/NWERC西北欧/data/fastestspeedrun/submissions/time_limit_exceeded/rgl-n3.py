#!/usr/bin/env python3

res = 0

n = int(input()) + 1
edge = [[i == j for j in range(n)] for i in range(n)]
cost = [[     0 for j in range(n)] for i in range(n)]
for i in range(1, n):
  row = list(map(int, input().split()))
  x,t = row[0],row[1]
  res += t
  edge[x][i] = True
  for j in range(n):
    cost[j][i] = row[2+j] - t

for i in range(n):
  for j in range(n):
    for k in range(n):
      edge[j][k] = edge[j][k] or edge[j][i] and edge[i][k]

for i in range(n):
  for j in range(n):
    if edge[i][j]:
      cost[i][j] = 0
      for k in range(n):
        cost[i][k] = min(cost[i][k], cost[j][k])

for i in range(1,n):
  if min([not edge[j][i] or edge[i][j] and (cost[n-1][i],i) <= (cost[n-1][j],j) for j in range(n)]):
    rcost = cost[n-1][i]
    res += rcost
    for j in range(n):
      if edge[i][j] and edge[j][i]:
        for k in range(n):
          cost[k][j] -= rcost

for i in range(n):
  for j in range(n):
    for k in range(n):
      cost[j][k] = min(cost[j][k], max(0,cost[j][i]) + max(0,cost[i][k]))

print(cost[0][-1]+res)
