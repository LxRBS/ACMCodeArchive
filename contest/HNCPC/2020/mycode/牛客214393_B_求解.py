# encoding: utf-8
"""
  �õ��Ȧд��һ��ͼ��ͼ�е�����Ҫô��2020Ҫô��2018��Ҫ������ж�
  ������ͨ�Լ��ɡ�2018��3���������2020ֻ��2���� 
"""
from math import sqrt, gcd, log10, log2
from queue import Queue
from random import randint
from random import shuffle
from queue import Queue, PriorityQueue
from decimal import getcontext, Decimal
from collections import OrderedDict
from collections import Counter
from random import *
import sys
sys.setrecursionlimit(10 ** 6)


Ans = 0
DR = [-1,1,0,0]
DC = [0,0,-1,1]


def dfs(n, m, s, flag, r, c):
    global Ans, DR, DC
    flag[r][c] = True
    for dr, dc in zip(DR, DC):
        nr = r + dr
        nc = c + dc
        if 0<=nr<n and 0<=nc<m:
            if s[nr][nc] == '.' and (not flag[nr][nc]):
                dfs(n, m, s, flag, nr, nc)
        else: Ans = 0


def f(n, m, s):
    global Ans
    flag = [[False for i in range(m)] for j in range(n)]
    ret = 0
    for i in range(n):
        for j in range(m):
            if s[i][j] == '.' and (not flag[i][j]):
                Ans = 1
                dfs(n, m, s, flag, i, j)
                ret += Ans
    return ret


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    fp = sys.stdin
    while True:
        line = fp.readline()
        if not line:
            break
        n, m = [int(i) for i in line.split()]
        s = []
        for i in range(n):
            s.append(input())
        ans = f(n, m, s)
        # print(ans)
        if ans == 3: print(2018)
        else: print(2020)




