#!/usr/bin/env python3

import sys

MAX_SUM = 1e6

n = int(sys.stdin.readline())
arr = [int(x) for x in sys.stdin.readline().split(' ')]
next_one = [0] * (n + 1)
i = n - 1
while i >= 0:
  if arr[i] == 1:
    next_one[i] = max(next_one[i + 1], i)
  i -= 1

ans, i = 0, 0
while i < n:
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
      if prod - sum > n - j - 1: break
      if sum == prod: ans += 1
    j += 1
  i += 1
        
print (ans)
