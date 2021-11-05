# encoding: utf-8
"""
    有一棵树，每次随机选一个点，
    将其及其子孙节点全部删除，问将树删空需要的操作次数期望
    树根的概率必然为1
    一级子节点的概率为树根排在其后的概率，1/2
    二级子节点的概率为树根与一级均排在其后的概率，1/3
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


