"""
中心线重合的圆和梯形
问圆是否能穿过梯形
"""
# encoding: utf-8
import sys
import decimal
from decimal import Decimal
from math import acos, sqrt, pi, gcd, fabs, atan2, atan, tan, cos, sin
import random
import datetime
sys.setrecursionlimit(10 ** 6)


def proc(r, a, b, h):
    if b > r + r:
        print("Drop")
        return
    theta = atan(0.5*(a-b)/h)
    ans1 = 0.5 * b * tan(theta)
    xie = 0.5 * b / cos(theta)
    shegnxia = r - xie
    ans2 = shegnxia / sin(theta)
    ans = ans1 + ans2
    print("Stuck")
    print('%.12f' % ans)


if __name__ == '__main__':
    r, a, b, h = [int(i) for i in input().split()]
    proc(r, a, b, h)


