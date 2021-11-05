# encoding: utf-8
"""
    n种，每次等概率，问齐全需要多少次
    要求输出最简真分数
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


def gcd(a, b):
    while b != 0:
        r = b; b = a % b; a = r
    return a


class Rational:
    def __init__(self, a, b):
        self.fenzi, self.fenmu = a, b
        g = gcd(self.fenzi, self.fenmu)
        self.fenzi //= g; self.fenmu //= g

    def __add__(self, other):
        return Rational(self.fenzi * other.fenmu + self.fenmu * other.fenzi, self.fenmu * other.fenmu)

    def __str__(self):
        a = self.fenzi // self.fenmu
        b = self.fenzi % self.fenmu
        if 0 == b:
            return str(a)
        first = str(b)
        third = str(self.fenmu)
        second = "".join(['-' for i in range(len(third))])
        if 0 == a:
            return first + "\n" + second + "\n" + third
        a = str(a)
        second = a + second
        t = "".join([' ' for i in range(len(a))])
        first = t + first
        third = t + third
        return first + "\n" + second + "\n" + third


def f1():
    """
    令Di为已经收集到i种，再到n种的期望次数
    则Dn=0
    Di = i/n * Di + (n-i)/n*D[i+1] + 1
    所以 Di = D[i+1] + n / (n-i)
    """
    n = int(input())
    d = [0 for i in range(n+1)]
    d[n] = Rational(0, 1)
    for i in range(n-1, -1, -1):
        d[i] = d[i+1] + Rational(n, n-i)
    print(d[0])


def f2():
    """
    已有i种时，买到下一种的概率是(n-i)/n，所以期望次数是n/(n-i)
    累加求和
    1 + n/(n-1) + n/(n-2) + ... + n
    ...
    """
    n = int(input())
    ans = Rational(0, 1)
    for i in range(n):
        ans = ans + Rational(n, n - i)
    print(ans)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    # f1()
    f2()

