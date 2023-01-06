# -*- coding: utf-8 -*-
import sys
sys.setrecursionlimit(10**6)

def proc():
    a, b, c, x, y = [int(i) for i in input().split()]
    if a >= x: x = 0
    else: x -= a
    if b >= y: y = 0
    else: y -= b
    return 'YES' if c >= x + y else 'NO'

if __name__ == "__main__":
    # sys.stdin = open('1.txt')
    pass
    nofkase = int(input())
    for kase in range(nofkase):
        print(proc())