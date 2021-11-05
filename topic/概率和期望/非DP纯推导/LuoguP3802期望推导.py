# encoding: utf-8
"""
    1~7的数字各有ai个
    将其排成一排，问恰好成为全排列的子串的数量期望
    可以重叠
    首先考虑前7个就能全排列的概率
    设N是所有的数字数量
    a1/N * a2/(N-1) * ... * a7/(N-6) * 7!
    再考虑第8个数字能全排列的概率，实际上与前者相同，类似于无放回采样
    也可以用条件概率计算，相当于第一个随意，后7个全排列
    a1/N * ( (a1-1)/(N-1) * ... * a7/(N-7) * 7! )
  + a2/N * ( a1/(N-1) * (a2-1)/(N-2) * ... * a7/(N-7) * 7! )
  + ...
     所以在任意位置上，当然是从7到N的位置，称为全排列的概率是相等的
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


