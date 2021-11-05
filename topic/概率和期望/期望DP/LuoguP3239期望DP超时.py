# encoding: utf-8
"""
    n张牌，r轮
    每一轮：依次考虑每张牌，如果已经用过，跳过，最后一张也跳过则该轮结束
    如果没用过，以pi概率发动技能，如果成功，获得di，该轮结束
    不成功，再考虑下一张
    问整个游戏的期望
    每张牌只能发动一次，设Pi为概率，则期望为SIGMA{Pi*di}
    第一张牌发动概率1-(1-p1)**r
    第二张牌的发动概率...
    令Dij为第i轮选中j张的概率
    Dij = D[i-1][j-1] * (1-(1-pi)**(r-j+1)), 如果第i张牌发动
    Dij = D[i-1][j] * (1-pi**(r-j))，第i张牌没有发动
    第i张牌发动的概率Pi = SIGMA{D[i-1][j]*(1-(1-Pi)**(r-j)),j从0到i-1}
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    nofkase = int(input())
    for kase in range(nofkase):
        n, r = [int(i) for i in input().split()]
        p = [0.0 for i in range(n+1)]
        d = [0 for i in range(n+1)]
        for i in range(1, n+1):
            a = input().split()
            p[i], d[i] = float(a[0]), int(a[1])
        D = [[0 for i in range(233)]for j in range(233)]
        D[0][0] = 1
        for i in range(1, n+1):
            for j in range(0, min(i, r)+1):
                D[i][j] = D[i-1][j-1] * (1-(1-p[i])**(r-j+1)) if j != 0 else 0
                D[i][j] += D[i-1][j] * (1 - p[i]) ** (r - j)
        ans = 0.0
        for i in range(1, n+1):
            for j in range(0, min(i, r)):
                ans += d[i] * D[i-1][j] * (1 - (1 - p[i]) ** (r - j))
        print(ans)

