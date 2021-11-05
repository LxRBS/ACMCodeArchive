# encoding: utf-8
"""
  ����Ϊn���ַ�������i��λ����ΪO�ĸ���Ϊpi������Ϊx
  �ַ����ĵ÷�Ϊ����O��������ƽ����
  ��"OOXXOOOXOO"�ĵ÷�Ϊ4+9+4=17
  �ʵ÷�����
  DiΪ��iλ������O��������EiΪ��iλ�õĵ÷�����
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
