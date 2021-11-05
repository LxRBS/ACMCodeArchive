# encoding: utf-8
"""
  长度为n的字符串，第i个位置上为O的概率为pi，否则为x
  字符串的得分为连续O的数量的平方和
  如"OOXXOOOXOO"的得分为4+9+4=17
  问得分期望
  Di为到i位置连续O的期望，Ei为到i位置的得分期望
  Di = (D[i-1]+1)*pi
  Ei = E[i-1] + Pi * (2D[i-1] + 1)
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    n = int(input())
    p = [float(i) for i in input().split()]
    d = [0.0 for i in range(n)]
    e = [0.0 for i in range(n)]
    d[0] = e[0] = p[0]
    for i in range(1, n):
        d[i] = p[i] * (d[i-1] + 1.0)
        e[i] = e[i-1] + p[i] * (2.0 * d[i-1] + 1)
    print(e[n-1])
