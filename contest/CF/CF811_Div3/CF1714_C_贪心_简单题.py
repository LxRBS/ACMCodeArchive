"""
给定一个数s，要求求出一个数n，满足
1 n的各位数字之和为s
2 n的各位数组各不一样
3 满足前两条的最小的n
贪心即可
"""
# -*- coding: utf-8 -*-
import sys
sys.setrecursionlimit(10**6)


def proc():
    n = int(input())
    s = ''
    for i in range(9, 0, -1):
        if n <= i:
            s += str(n)
            break
        s += str(i)
        n -= i
    s = ''.join(reversed(s))
    return s

if __name__ == "__main__":
    # sys.stdin = open('1.txt')
    pass
    nofkase = int(input())
    for kase in range(nofkase):
        print(proc())