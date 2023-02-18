"""
N×N的方阵，N是奇数，每格有一个东西
每步可以将物品移动到相邻格子
问最少多少步将所有物品移动到同一格

显然所有物品移动到中心应该是最少的
计算一下公式
或者N在5E5，O(N)也能过
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
        