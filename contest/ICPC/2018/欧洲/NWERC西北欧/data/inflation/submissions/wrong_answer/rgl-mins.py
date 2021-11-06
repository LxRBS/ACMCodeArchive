#!/usr/bin/env python3
res = min(b/a for a,b in zip(range(1,int(input())+1), sorted(map(int, input().split()))))
print('impossible' if res > 1 else '%.6f' % (res))
