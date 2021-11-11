# encoding: utf-8
"""
给定n，要求找到一个x，满足
x+2x+4x+...+2^(k-1)x == n
挨个看是否整除即可：3,7,15,31,...
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    nokfase = int(input())
    for kase in range(nokfase):
        n = int(input())
        t = 4
        while True:
            if n % (t - 1) == 0:
                break
            t *= 2
        print(n // (t - 1))



