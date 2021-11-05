# encoding: utf-8
"""
    n个中间有x个
    m个中间有y个
    任取一堆，不放回取两个，已知第一个取中
    问第二个也取中的概率
    P(2|1) = P(1&&2)/P(1)
    P(1) = 1/2 * (x / n + y / m)
    P(1&&2) = 1/2 * (x / n * (x-1) / (n - 1) + y / m * (y-1) / (m-1))
"""
from math import sqrt
import sys
sys.setrecursionlimit(10**6)


def gcd(a, b):
    while b != 0:
        r = b
        b = a % b
        a = r
    return a


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    n, m, x, y, t = [int(i) for i in input().split()]
    fenzi = x * (x - 1) * m * (m - 1) + y * (y - 1) * n * (n - 1)
    fenmu = (n - 1) * (m - 1) * (m * x + n * y)
    if 0 == fenzi:
        fenmu = 1
    else:
        g = gcd(fenzi, fenmu)
        fenzi, fenmu = fenzi // g, fenmu // g
    if 1 == t:
        print(str(fenzi) + '/' + str(fenmu))
    else:
        print("%.3f" % (fenzi/fenmu))


