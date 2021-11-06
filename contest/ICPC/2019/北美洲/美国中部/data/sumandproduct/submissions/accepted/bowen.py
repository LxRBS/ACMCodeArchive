#!/usr/bin/env python2

import sys

MAX_SUM = 2e14

n = int(sys.stdin.readline())
arr = [int(x) for x in sys.stdin.readline().split()]
next_one = [-1] * (n + 1)
for i in range(n-1, -1, -1):
  if arr[i] == 1:
    next_one[i] = max(next_one[i + 1], i)

ans = 0
for i in range(n):
  sum, prod, j = arr[i], arr[i], i+1
  while j < n:
    if arr[j] == 1:
      cnt_one = next_one[j] - j + 1
      if 1 <= prod - sum <= cnt_one: ans += 1
      sum += cnt_one
      j = next_one[j]
    else:
      sum += arr[j]
      prod *= arr[j]
      if prod > MAX_SUM: break
      if sum == prod: ans += 1
    j += 1
        
print (ans)
