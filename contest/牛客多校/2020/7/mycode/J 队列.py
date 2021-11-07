# encoding: utf-8
from math import sqrt, gcd, log10, log2
from queue import Queue
from random import randint
from random import shuffle
from queue import Queue
from decimal import getcontext, Decimal
from collections import OrderedDict
import sys
sys.setrecursionlimit(10 ** 6)
"""
  A~Z��ʾָ�룬����ָ��a~z��object
  A.a~zҲ����ָ�룬����ָ��object
  A.a�����嵱�ҽ���Aȷʵָ��һ��object����object��a�����Ա
  ��A~Z���п���ָ���object
"""


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    d = {}
    for si in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
        d[si] = set()
    src = []
    worklist = Queue()
    n = int(input())
    for i in range(n):
        tmp = input().split('=')
        tmp[0] = tmp[0].strip()
        tmp[1] = tmp[1].strip()
        src.append(tmp)
        if 1 == len(tmp[0]) and 1 == len(tmp[1]) and tmp[1].islower():  # A = a
            if tmp[1] not in d[tmp[0]]:
                d[tmp[0]].add(tmp[1])
                worklist.put(tmp[0])
    while worklist.empty() is False:
        while worklist.empty() is False:
            h = worklist.get()
            for a1, a2 in src:
                if 1 == len(a1) and a2 == h:  # A = B
                    origin_len = len(d[a1])
                    d[a1] = d[a1] | d[a2]  # ����
                    if origin_len != len(d[a1]):
                        worklist.put(a1)
        for a1, a2 in src:
            if 3 == len(a1) and 1 == len(a2) and a2.isupper():  # A.a = B
                for x in d[a1[0]]:
                    if x.islower():  # x��A��ָ���object
                        tmp = x + a1[1::]
                        if tmp not in d:
                            d[tmp] = set()
                        d[tmp] = d[tmp] | d[a2]
        for a1, a2 in src:
            if 1 == len(a1) and 3 == len(a2):  # A = B.a
                for x in d[a2[0]]:
                    tmp = x + a2[1::]
                    if tmp not in d:
                        d[tmp] = set()
                    origin_cnt = len(d[a1])
                    d[a1] = d[a1] | d[tmp]
                    if origin_cnt != len(d[a1]):
                        worklist.put(a1)
    for si in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
        print(si, ': ', sep='', end='')
        tmp = list(d[si])
        tmp.sort()
        print(''.join(tmp))


