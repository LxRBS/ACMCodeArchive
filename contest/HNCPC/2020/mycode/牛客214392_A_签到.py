# encoding: utf-8
from math import sqrt, gcd, log10, log2
from queue import Queue
from random import randint
from random import shuffle
from queue import Queue, PriorityQueue
from decimal import getcontext, Decimal
from collections import OrderedDict
from collections import Counter
from random import *
import sys
sys.setrecursionlimit(10 ** 6)


if __name__ == '__main__':
    # sys.stdout = open('H:\\CppProject\\acmt_win\\1.txt', 'w')
    fp = sys.stdin
    while True:
        line = fp.readline()
        if not line:
            break
        n = int(line)
        s = input()
        i = 0
        cnt = 0
        while i < n:
            if s[i:i+4] == '2020':
                cnt += 1
                i += 4
            else: i += 1
        print(cnt)














