"""
����N��M��Ҫ����һ�����飬ʹ�����ΪM
��SIGMA|ai-a[i+1]|���

�۲��������ɵõ��𰸣�һ��Ϊ2M
�����������
"""
# encoding: utf-8
import sys
sys.setrecursionlimit(10**6)


def f(n, m):
    if 1 == n:
        return 0
    if 2 == n:
        return m
    return m + m


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    nofkase = int(input())
    for kase in range(nofkase):
        n, m = [int(i) for i in input().split()]
        print(f(n, m))