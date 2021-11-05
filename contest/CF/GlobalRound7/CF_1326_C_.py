# encoding: utf-8
"""
给一个长度为N的排列，以及一个整数K
将该排列划分为K个部分
定义pv=SIGMA(max(pi),i从1到K)
找出pv的最大值，以及能够达到这个最大值的划分的数量

划分的最大值显然是从N加到N-K+1。
然后划分总数显然是之间的隔断的数量的连乘积
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    MOD = 998244353
    # sys.stdin = open('1.txt', 'r')
    n, k = [int(i) for i in input().split()]
    a = [int(i) for i in input().split()]
    pos = []
    pre = -1
    for i, ai in enumerate(a):
        if ai > n - k:
            if pre == -1:
                pre = i
            else:
                pos.append(i - pre)
                pre = i
    ans = 1
    for poi in pos:
        ans = ans * poi % MOD
    print((n+n-k+1)*k//2, ans)



