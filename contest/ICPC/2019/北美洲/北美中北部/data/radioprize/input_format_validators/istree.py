#!/usr/bin/env python3

# verify that the input is a tree

import sys
import collections

n = int(sys.stdin.readline())
sys.stdin.readline() # skip the taxes
tree = collections.defaultdict(set)
for _ in range(n-1):
    u, v, w = tuple(map(int, sys.stdin.readline().split()))
    tree[u].add(v)
    tree[v].add(u)

print('tree', tree)

s = [1]
visited = set([1])
while s:
    c = s.pop()
    for x in tree[c] - visited:
        visited.add(x)
        s.append(x)

print('visited', visited)

assert visited == set(range(1,n+1)), visited

sys.exit(42)

