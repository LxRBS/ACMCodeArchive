#!/usr/bin/env python
import sys
import itertools

def parse_input():
    n = int(raw_input())
    xs, ys = [], []
    t = []
    for line in sys.stdin:
        l = line.split(' ', 1)
        xs.append(l[0])
        ys.append(l[1])
    return map(int, xs), map(int, ys)

def get_optimal_solution(ls):
    """ list of (count, position) """
    erg = []

    maxmerge = 0
    for i in ls:
        erg.append((1, i))
        cur_merge = 0
        while len(erg) > 1:
            last = erg.pop()
            prev = erg.pop()
            if prev[0] * last[1] < last[0] * prev[1]:
                num = last[0] + prev[0]
                su = last[1] + prev[1]
                erg.append((num, su))
                cur_merge += 1
            else:
                erg.append(prev)
                erg.append(last)
                break
        maxmerge = max(cur_merge, maxmerge)

    return maxmerge

xs, ys = parse_input()
print(get_optimal_solution(xs) + get_optimal_solution(ys))
