#!/usr/bin/env python3
res = [b/a for a,b in zip(range(1,int(input())+1), sorted(map(int, input().split())))]
print('impossible' if max(res) > 1 else '%.20f' % (min(res)+0.9999*1e-6))
