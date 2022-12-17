"""
给定字符串S和T，其中S全由a构成。每次操作可以将S中的一个a换成T
可以进行任意次操作，问一共能得到多少个不同的字符串
分情况讨论一下，直接有结论
假设T=a，则只有一种，就是S本身
假设T=xxxxaxxxx，则肯定是无穷种
否则，就是换与不换的问题，2^n，其中n是S的长度
"""
import sys
sys.setrecursionlimit(10**6) 

def proc(s, t):
    nt = len(t)
    ns = len(s)
    if 1 == nt:
        if 'a' == t: return 1
        return 1 << ns
    if 'a' in t: return -1
    return 1 << ns

if __name__ == '__main__':
    # sys.stdin = open('1.txt',   'r')
    nofkase = int(input())
    for kase in range(nofkase):
        s = input()
        t = input()
        print(proc(s, t))
            


