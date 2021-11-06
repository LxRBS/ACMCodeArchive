#!/usr/bin/python3
import collections
N = int(input())
dict = []
for i in range(N) :
  x,f = [float(x) for x in input().split()]
  dict.append([x,f])
  
dict.sort()

ans = 00000000000

for i in range(1, N):
  x = dict[i - 1][0]
  fx = dict[i - 1][1]
  y = dict[i][0]
  fy = dict[i][1]
  ans = max(ans, abs(fx-fy) / abs(x - y) )

print(ans)

