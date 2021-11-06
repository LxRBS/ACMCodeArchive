#!/usr/bin/env python
import collections

n,e,b = map(int, raw_input().split())
b = set(map(int, raw_input().split()))

dp = [[(-n,-1) for j in range(2)] for i in range(n+1)]
dp[0][e % 2] = (0, -1)
for i in range(1,n+1):
  for j in ([0] if i+1 in b else [0,1]):
    for k in range(2):
      score = dp[i-1][k][0] + int(i<n and j<>k)
      if score <= e:
        dp[i][j] = max(dp[i][j], (score, k))

res = collections.deque()
bit = 0
for i in range(n,0,-1):
  bit = dp[i][bit][1]
  res.appendleft(str(bit))

print ''.join(res)
