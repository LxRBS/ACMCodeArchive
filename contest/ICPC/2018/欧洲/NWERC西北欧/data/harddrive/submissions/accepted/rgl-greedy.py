#!/usr/bin/env python

n,e,b = map(int, raw_input().split())
b = set(map(int, raw_input().split()))

# Start with all 1s
v = [int(i+1 not in b) for i in range(n)]
e -= sum([int(v[i] <> v[i+1]) for i in range(n-1)])

# Fix the parity with the first digit (1000 -> 0000 / 1110 -> 0110)
if e % 2 == 1:
  v[0] = 0
  e += int(v[1] == 0) - int(v[1] == 1)

# Remove 111s (011110 -> 000000) while we have too many changes
for i in range(n-1,0,-1):
  if e < 0 and v[i] == 1:
    e += int(v[i-1] == 0) * 2
    v[i] = 0

# Add 101s (0111110 -> 0101010) while we have too few changes
for i in range(n-2,0,-1):
  if e >= 2 and v[i] == 1 and v[i+1] == 1 and v[i-1] == 1:
    v[i] = 0
    e -= 2

print ''.join(map(str, v))
