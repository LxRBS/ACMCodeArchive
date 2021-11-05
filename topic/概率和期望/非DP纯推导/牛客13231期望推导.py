# encoding: utf-8
"""
    n�����ų�һ���ܲ���ÿ���˼��u���ٶ�v
    ���һ���˻����������ǰ�ܣ�������ͷu��Ȼ�󽫻ص�v
    ÿ������������Ϊci��ÿ��˥��di��
    �����i�ǵ�j����ǰ׷�ģ����ٶ���ci-(j-1)*di
    ������һ�ֵ�����ʱ���Ƕ���
    E = SIGMA{1/n!*��ǰ���е���ʱ��}
    ���ǵ�ÿ���˶�����ÿ��λ�õȸ��ʵĳ���
    E = SIGMA{1/n*ÿ����������λ���������ʱ��}
"""
from math import sqrt
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    n, v, u = input().split()
    n, v, u = int(n), float(v), float(u)
    c = [float(i) for i in input().split()]
    d = [float(i) for i in input().split()]
    ans = 0.0
    for i in range(n):
        ret = 0.0
        for j in range(n):
            ret += 1.0 / (c[i] - j*d[i] - v)
        ans += ret
    print("%.3f" % (ans*u))