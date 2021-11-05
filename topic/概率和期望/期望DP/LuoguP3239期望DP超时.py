# encoding: utf-8
"""
    n���ƣ�r��
    ÿһ�֣����ο���ÿ���ƣ�����Ѿ��ù������������һ��Ҳ��������ֽ���
    ���û�ù�����pi���ʷ������ܣ�����ɹ������di�����ֽ���
    ���ɹ����ٿ�����һ��
    ��������Ϸ������
    ÿ����ֻ�ܷ���һ�Σ���PiΪ���ʣ�������ΪSIGMA{Pi*di}
    ��һ���Ʒ�������1-(1-p1)**r
    �ڶ����Ƶķ�������...
    ��DijΪ��i��ѡ��j�ŵĸ���
    Dij = D[i-1][j-1] * (1-(1-pi)**(r-j+1)), �����i���Ʒ���
    Dij = D[i-1][j] * (1-pi**(r-j))����i����û�з���
    ��i���Ʒ����ĸ���Pi = SIGMA{D[i-1][j]*(1-(1-Pi)**(r-j)),j��0��i-1}
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

