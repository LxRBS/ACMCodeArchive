"""
����������������A��B������ΪN
ÿ�β�����Ai��Bj���н�����ij������ȣ�
K�β�����A�����Ϳ����Ƕ���

̰�ģ���A����С�Ĳ�����B�����Ĳ��ֽ�������
"""
# encoding: utf-8
import sys
from math import sqrt
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    nofkase = int(input())
    for kase in range(nofkase):
        n, k = [int(i) for i in input().split()]
        a = [int(i) for i in input().split()]
        b = [int(i) for i in input().split()]
        a.sort()
        b.sort(reverse=True)
        ans = 0
        i = 0
        while i < k and b[i] > a[i]:
            ans += b[i]
            i += 1
        ans += sum(a[i::])
        print(ans)

