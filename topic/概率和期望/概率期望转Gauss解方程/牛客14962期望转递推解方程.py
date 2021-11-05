# encoding: utf-8
"""
    Alice从[l, r]中任选一个数
    Bob从[L, R]中任选一个数
    胜者从负者那里拿一个糖果
    初始分别有n和m个，问Alice赢完的概率
    令Di为Alice有i个糖果能获胜的概率，显然
    Di = pD[i+1] + (1-p)D[i-1]
    而且D[0] = 0, D[n+m] = 1
    这是一个方程，但是n+m太大，不能高斯消元
    D1 = pD2，记作 D1 = k1D2
    D2 = pD3 + (1-p)D1，记作 D2 = k2D3, 其中 k2 = p/(1-(1-p)k1)
    D3 = pD4 + (1-p)D2，记作 D3 = k3D3, 其中 k3 = p/(1-(1-p)k2)
    D[n+m-1] = k[n+m-1] * 1 = p / (1-(1-p)k[n+m-2])
    可以一直算出k[n+m-1]，累乘即可
    p是Alice单次获胜的概率，n和m比较小，直接计算所有可能性即可
"""
from math import sqrt
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    n, l, r = [int(i) for i in input().split()]
    m, L, R = [int(i) for i in input().split()]
    if 0 == n:
        print("0.00000")
        exit(0)
    if 0 == m:
        print("1.00000")
        exit(0)
    # 首先计算p
    win, tmp = 0, 0
    for i in range(l, r+1):
        for j in range(L, R+1):
            if i == j: continue
            tmp += 1
            win = win + (1 if i > j else 0)
    p = win / tmp
    ans, k = 1.0, p
    for i in range(1, n+m):
        if i >= n: ans *= k
        k = p / (1 - (1 - p) * k)
    print("%.5f" % (ans))

