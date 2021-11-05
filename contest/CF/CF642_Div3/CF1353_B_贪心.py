"""
给定两个正数数组A和B，长度为N
每次操作将Ai和Bj进行交换（ij可以相等）
K次操作后，A的最大和可能是多少

贪心，将A的最小的部分与B的最大的部分交换即可
"""
# encoding: utf-8
import sys
from math import sqrt
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    nofkase = int(input())
    for kase in range(nofkase):
        n, k = [int(i) for i in input().split()]
        a = [int(i) for i in input().split()]
        b = [int(i) for i in input().split()]
        a.sort()
        b.sort(reverse=True)
        ans = 0
        i = 0
        while i < k and b[i] > a[i]:
            ans += b[i]
            i += 1
        ans += sum(a[i::])
        print(ans)

