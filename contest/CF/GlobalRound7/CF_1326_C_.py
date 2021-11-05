# encoding: utf-8
"""
��һ������ΪN�����У��Լ�һ������K
�������л���ΪK������
����pv=SIGMA(max(pi),i��1��K)
�ҳ�pv�����ֵ���Լ��ܹ��ﵽ������ֵ�Ļ��ֵ�����

���ֵ����ֵ��Ȼ�Ǵ�N�ӵ�N-K+1��
Ȼ�󻮷�������Ȼ��֮��ĸ��ϵ����������˻�
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    MOD = 998244353
    # sys.stdin = open('1.txt', 'r')
    n, k = [int(i) for i in input().split()]
    a = [int(i) for i in input().split()]
    pos = []
    pre = -1
    for i, ai in enumerate(a):
        if ai > n - k:
            if pre == -1:
                pre = i
            else:
                pos.append(i - pre)
                pre = i
    ans = 1
    for poi in pos:
        ans = ans * poi % MOD
    print((n+n-k+1)*k//2, ans)



