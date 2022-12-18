"""
给定一个数组，每次可以删除最左边的数，问最少多少次操作可以将数组变成没有重复的元素
"""
# -*- coding: utf-8 -*-
import sys
sys.setrecursionlimit(10**6)


def proc():
    n = int(input())
    a = [int(i) for i in input().split()]
    s = set()
    for i, ai in enumerate(a[::-1]):
        if ai in s: return n - i
        s.add(ai)
    return 0

if __name__ == "__main__":
    # sys.stdin = open('1.txt')
    pass
    nofkase = int(input())
    for kase in range(nofkase):
        print(proc())