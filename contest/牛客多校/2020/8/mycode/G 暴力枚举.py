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
    ÿ������4�����ԣ�ÿ��������3��ֵ������֮�⻹��*���ԣ���ʾͨ���
    ����N���ƣ����Ƿ���ѡ��3�ţ�ʹ��ÿ�����Ե�ȡֵҪôȫ��һ��Ҫôȫ��һ��
    ��������ѭ������
    N�ﵽһ�������Ժ�20����21������Ȼ�н⣬���ֱ�ӱ�������
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
        # �Ƿ����
        tmp = {a[i]: 1}
        add(tmp, b[i])
        add(tmp, c[i])
        if len(tmp) == 3: pass  # ������ͬ
        elif tmp[a[i]] == 3: pass  #����ȫ��ͬ
        elif '*' in tmp: pass  # ���ǾͿ���
        else: return False
    return True


def proc():
    global N, A, ans, B
    ans = []
    if N <= 2: return  # ֱ��û��
    # ֱ�ӷ��ش�
    if ('*', '*', '*', '*') in A and len(A[('*', '*', '*', '*')]) >= 2:
        tmp = A[('*', '*', '*', '*')]
        ans.append(tmp[0])
        ans.append(tmp[1])
        for i in range(N):
            if i != tmp[0] and i != tmp[1]:
                ans.append(i)
        return
    # ������û��3��
    for k, a in A.items():
        if len(a) >= 3:
            ans = a[0:3]
            return
    # ����
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


