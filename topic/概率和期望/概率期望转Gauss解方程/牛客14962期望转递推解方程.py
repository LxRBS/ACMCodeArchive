# encoding: utf-8
"""
    Alice��[l, r]����ѡһ����
    Bob��[L, R]����ѡһ����
    ʤ�ߴӸ���������һ���ǹ�
    ��ʼ�ֱ���n��m������AliceӮ��ĸ���
    ��DiΪAlice��i���ǹ��ܻ�ʤ�ĸ��ʣ���Ȼ
    Di = pD[i+1] + (1-p)D[i-1]
    ����D[0] = 0, D[n+m] = 1
    ����һ�����̣�����n+m̫�󣬲��ܸ�˹��Ԫ
    D1 = pD2������ D1 = k1D2
    D2 = pD3 + (1-p)D1������ D2 = k2D3, ���� k2 = p/(1-(1-p)k1)
    D3 = pD4 + (1-p)D2������ D3 = k3D3, ���� k3 = p/(1-(1-p)k2)
    D[n+m-1] = k[n+m-1] * 1 = p / (1-(1-p)k[n+m-2])
    ����һֱ���k[n+m-1]���۳˼���
    p��Alice���λ�ʤ�ĸ��ʣ�n��m�Ƚ�С��ֱ�Ӽ������п����Լ���
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
    # ���ȼ���p
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

