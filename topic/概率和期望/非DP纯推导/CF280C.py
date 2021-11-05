# encoding: utf-8
"""
    ��һ������ÿ�����ѡһ���㣬
    ���估������ڵ�ȫ��ɾ�����ʽ���ɾ����Ҫ�Ĳ�����������
    �����ĸ��ʱ�ȻΪ1
    һ���ӽڵ�ĸ���Ϊ�����������ĸ��ʣ�1/2
    �����ӽڵ�ĸ���Ϊ������һ�����������ĸ��ʣ�1/3
    ...
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    n = int(input())
    edges = [[] for i in range(n+1)]
    for i in range(1, n):
        a, b = [int(i) for i in input().split()]
        edges[a].append(b); edges[b].append(a)
    d = [0 for i in range(n+1)]
    q = Queue()
    q.put(1)
    d[1] = 1
    ans = 1.0
    while q.empty() is False:
        u = q.get()
        for v in edges[u]:
            if d[v] == 0:
                d[v] = d[u] + 1
                q.put(v)
                ans += 1 / d[v]
    print(ans)


