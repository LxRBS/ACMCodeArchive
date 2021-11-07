# encoding: utf-8
from math import sqrt, gcd, log10, log2
from queue import Queue
from random import randint
from random import shuffle
from queue import Queue
from decimal import getcontext, Decimal
from collections import OrderedDict
import sys
sys.setrecursionlimit(10 ** 6)

"""
    每张牌有4种属性，每个属性有3种值，除此之外还有*属性，表示通配符
    给定N张牌，问是否能选出3张，使得每种属性的取值要么全部一样要么全不一样
    暴力三重循环即可
    N达到一定数量以后（20还是21），必然有解，因此直接暴力即可
"""


def read():
    global N, A, B
    A = {}
    B = []
    N = int(input())
    for i in range(N):
        s = input()
        s = s.split('][')
        s[0] = s[0][1::]
        s[3] = s[3][0:len(s[3])-1]
        k = tuple(s)
        B.append(k)
        if k in A:
            A[k].append(i)
        else:
            A[k] = [i]


def add(d, k):
    if k in d: d[k] += 1
    else: d[k] = 1


def isOK(a, b, c):
    for i in range(4):
        # 是否相等
        tmp = {a[i]: 1}
        add(tmp, b[i])
        add(tmp, c[i])
        if len(tmp) == 3: pass  # 各不相同
        elif tmp[a[i]] == 3: pass  #三个全相同
        elif '*' in tmp: pass  # 有星就可以
        else: return False
    return True


def proc():
    global N, A, ans, B
    ans = []
    if N <= 2: return  # 直接没有
    # 直接返回答案
    if ('*', '*', '*', '*') in A and len(A[('*', '*', '*', '*')]) >= 2:
        tmp = A[('*', '*', '*', '*')]
        ans.append(tmp[0])
        ans.append(tmp[1])
        for i in range(N):
            if i != tmp[0] and i != tmp[1]:
                ans.append(i)
        return
    # 搜索有没有3的
    for k, a in A.items():
        if len(a) >= 3:
            ans = a[0:3]
            return
    # 暴力
    for i in range(N-2):
        for j in range(i+1, N-1):
            for k in range(j+1, N):
                if isOK(B[i], B[j], B[k]):
                    ans = [i, j, k]
                    return
    ans = []
    return


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    N = 0
    A = None
    B = None
    ans = []
    nofkase = int(input())
    for kase in range(1, nofkase+1):
        read()
        proc()
        print('Case #%d: ' % kase, sep='', end='')
        if 0 == len(ans): print('-1')
        else:
            s = ' '.join([str(i+1) for i in ans])
            print(s)


