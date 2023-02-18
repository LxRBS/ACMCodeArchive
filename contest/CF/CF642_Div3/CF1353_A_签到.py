"""
给定N和M，要求构造一个数组，使得其和为M
且SIGMA|ai-a[i+1]|最大

观察样例即可得到答案，一般为2M
再判特殊情况
"""
# encoding: utf-8
import sys
sys.setrecursionlimit(10**6)


def f(n, m):
    if 1 == n:
        return 0
    if 2 == n:
        return m
    return m + m


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    nofkase = int(input())
    for kase in range(nofkase):
        n, m = [int(i) for i in input().split()]
        print(f(n, m))