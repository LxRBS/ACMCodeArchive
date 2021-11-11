# encoding: utf-8
"""
给定偶数n，要求构造一个数组：
前一半是偶数，后一半是奇数，且和相等，且所有数都不同
简单试验推测4的倍数可以构造，仅2的倍数则不行
前后排开，然后奇数和比偶数和少n/2，加到最后即可
"""
from math import sqrt
from queue import Queue
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    nokfase = int(input())
    for kase in range(nokfase):
        n = int(input())
        if n % 4 != 0:
            print("NO")
            continue
        print("YES")
        m = n // 2
        for i in range(1, m+1):
            print(i+i, end=' ')
        for i in range(m-1):
            print(i+i+1, end=' ')
        print(3*m-1)



