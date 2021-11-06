#!/usr/bin/env python3
import decimal
decimal.getcontext().prec = 30
res = [decimal.Decimal(b)/decimal.Decimal(a) for a,b in zip(range(1,int(input())+1), sorted(map(int, input().split())))]
print('impossible' if max(res) > 1 else str(min(res)))
