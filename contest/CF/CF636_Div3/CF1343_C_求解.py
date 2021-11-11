# encoding: utf-8
"""
给定数组A，子序列满足如下条件：
1 正负交替，或者负正交替
2 长度最长
3 和最大
问最大和是多少
在每个连续的正数或者负数中选最大值即可
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


def f(arr, start, n):
    if start == n:
        return 0, n
    mmax = arr[start]
    i = start
    if arr[start] > 0:
        while i < n and arr[i] > 0:
            mmax = max(mmax, arr[i])
            i += 1
        return mmax, i
    while i < n and arr[i] < 0:
        mmax = max(mmax, arr[i])
        i += 1
    return mmax, i


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    nokfase = int(input())
    for kase in range(nokfase):
        n = int(input())
        a = [int(i) for i in input().split()]
        sum = 0
        i = 0
        while i < n:
            mmax, i = f(a, i, n)
            sum += mmax
        print(sum)



