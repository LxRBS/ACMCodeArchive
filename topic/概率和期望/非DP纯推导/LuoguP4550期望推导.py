# encoding: utf-8
"""
    n����Ʊ����k�ι���kԪ���ȸ�����ĳһ����
    ��Ҫ�����������ռ���ȫ����������
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


def f1():
    """
    ��DiΪ�Ѿ��ռ���i�֣��ٵ�n�ֵ���������
    ��Dn=0
    Di = i/n * Di + (n-i)/n*D[i+1] + 1
    ���� Di = D[i+1] + n / (n-i)
    �ٿ��Ǽ۸���ΪAi,��An=0
    Ai = i/n * (Ai+(Di+1)) + (n-i)/n * (A[i+1]+D[i+1]+1)
    """
    n = int(input())
    d = [0 for i in range(n+1)]
    a = [0 for i in range(n + 1)]
    for i in range(n-1, -1, -1):
        d[i] = d[i+1] + n / (n - i)
        a[i] = i / (n - i) * d[i] + a[i+1] + d[i+1] + n / (n-i)
    print("%.2f" % (a[0]))


def f2():
    """
    ����i��ʱ������һ�ֵĸ�����(n-i)/n����������������n/(n-i)
    �ٿ�����һ�ֵ�ƽ���۸�Ӧ����֮ǰ�����ֵ���������֮��
    �������һ����100%��1�Σ��۸�Ϊ1
    ��ڶ�������������n/(n-1)��ƽ���۸���(1+n/(n-1))
    �����������������n/(n-2)��ƽ���۸���(1+n/(n-1)+n/(n-2))
    ...
    """
    n = int(input())
    ans = 0.0
    tmp = 0
    for i in range(0, n):
        tmp += n / (n - i)
        ans += n / (n - i) * tmp
    print("%.2f" % (ans))


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    # f1()
    f2()

