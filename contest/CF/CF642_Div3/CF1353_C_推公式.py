"""
N��N�ķ���N��������ÿ����һ������
ÿ�����Խ���Ʒ�ƶ������ڸ���
�����ٶ��ٲ���������Ʒ�ƶ���ͬһ��

��Ȼ������Ʒ�ƶ�������Ӧ�������ٵ�
����һ�¹�ʽ
����N��5E5��O(N)Ҳ�ܹ�
"""
# encoding: utf-8
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.std.in', 'r')
    nofkase = int(input())
    for kase in range(nofkase):
        n = int(input())
        n = n // 2
        print(n*(n+1)*(n+n+1)*8//6)
        