# encoding: utf-8
"""
    1~7�����ָ���ai��
    �����ų�һ�ţ���ǡ�ó�Ϊȫ���е��Ӵ�����������
    �����ص�
    ���ȿ���ǰ7������ȫ���еĸ���
    ��N�����е���������
    a1/N * a2/(N-1) * ... * a7/(N-6) * 7!
    �ٿ��ǵ�8��������ȫ���еĸ��ʣ�ʵ������ǰ����ͬ���������޷Żز���
    Ҳ�������������ʼ��㣬�൱�ڵ�һ�����⣬��7��ȫ����
    a1/N * ( (a1-1)/(N-1) * ... * a7/(N-7) * 7! )
  + a2/N * ( a1/(N-1) * (a2-1)/(N-2) * ... * a7/(N-7) * 7! )
  + ...
     ����������λ���ϣ���Ȼ�Ǵ�7��N��λ�ã���Ϊȫ���еĸ�������ȵ�
     E = (N-6) * a1/N * a2/(N-1) * ... * a7/(N-6) * 7!
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    a = [int(i) for i in input().split()]
    n = sum(a)
    if n < 7:
        print("0.000")
        exit(0)
    ans = (n - 6) * 720 * 7
    for i in range(7):
        ans = ans * a[i] / n
        n = n - 1
    print("%.3f" % (ans))


