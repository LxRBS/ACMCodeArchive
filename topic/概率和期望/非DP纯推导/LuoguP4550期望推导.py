# encoding: utf-8
"""
    n种邮票，第k次购买花k元，等概率买到某一种类
    问要把所有种类收集齐全的期望花费
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


def f1():
    """
    令Di为已经收集到i种，再到n种的期望次数
    则Dn=0
    Di = i/n * Di + (n-i)/n*D[i+1] + 1
    所以 Di = D[i+1] + n / (n-i)
    再考虑价格，设为Ai,且An=0
    Ai = i/n * (Ai+(Di+1)) + (n-i)/n * (A[i+1]+D[i+1]+1)
    """
    n = int(input())
    d = [0 for i in range(n+1)]
    a = [0 for i in range(n + 1)]
    for i in range(n-1, -1, -1):
        d[i] = d[i+1] + n / (n - i)
        a[i] = i / (n - i) * d[i] + a[i+1] + d[i+1] + n / (n-i)
    print("%.2f" % (a[0]))


def f2():
    """
    已有i种时，买到下一种的概率是(n-i)/n，所以期望次数是n/(n-i)
    再考虑下一种的平均价格，应该是之前所有种的期望次数之和
    即：买第一种是100%，1次，价格为1
    买第二种期望次数是n/(n-1)，平均价格是(1+n/(n-1))
    买第三种期望次数是n/(n-2)，平均价格是(1+n/(n-1)+n/(n-2))
    ...
    """
    n = int(input())
    ans = 0.0
    tmp = 0
    for i in range(0, n):
        tmp += n / (n - i)
        ans += n / (n - i) * tmp
    print("%.2f" % (ans))


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    # f1()
    f2()

