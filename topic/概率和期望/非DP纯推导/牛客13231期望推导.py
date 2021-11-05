# encoding: utf-8
"""
    n个人排成一排跑步，每个人间隔u，速度v
    最后一个人会以最高速往前跑，超过排头u，然后将回到v
    每个人最初最高速为ci，每轮衰减di，
    即如果i是第j个往前追的，其速度是ci-(j-1)*di
    问跑完一轮的期望时间是多少
    E = SIGMA{1/n!*当前排列的总时间}
    考虑到每个人都会在每个位置等概率的出现
    E = SIGMA{1/n*每个人在所有位置所需的总时间}
"""
from math import sqrt
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    n, v, u = input().split()
    n, v, u = int(n), float(v), float(u)
    c = [float(i) for i in input().split()]
    d = [float(i) for i in input().split()]
    ans = 0.0
    for i in range(n):
        ret = 0.0
        for j in range(n):
            ret += 1.0 / (c[i] - j*d[i] - v)
        ans += ret
    print("%.3f" % (ans*u))