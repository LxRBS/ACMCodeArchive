#!/usr/bin/env python3
n = int(input())
canisters = list(sorted(map(int, input().split())))
res = [b/a for a,b in zip(range(1,n+1), canisters)]
print('impossible' if max([0]+canisters[:-1]) >= n else '%.6f' % (min(res)))
