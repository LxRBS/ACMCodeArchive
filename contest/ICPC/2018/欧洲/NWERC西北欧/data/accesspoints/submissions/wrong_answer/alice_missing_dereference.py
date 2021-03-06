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

    for i in ls:
        erg.append((1, i))
        while len(erg) > 1:
            if erg[-2] < erg[-1]:
                last = erg.pop()
                prev = erg.pop()
                num = last[0] + prev[0]
                newmid = float(last[0] * last[1] + prev[0] * prev[1]) / num;
                erg.append((num, newmid))
            else:
                break

    return erg

def get_list_of_distances(ls, sol_l):
    erg = []
    i = 0
    for l in sol_l:
        for j in xrange(l[0]):
            erg.append(l[1] - ls[i])
            i += 1
    return erg

def calculate_distance(l_dx, l_dy):
    distances = [l_dx[i]**2 + l_dy[i]**2 for i in xrange(len(l_dx))]
    return sum(distances)

xs, ys = parse_input()
sol_x = get_optimal_solution(xs)
sol_y = get_optimal_solution(ys)
diff_x = get_list_of_distances(xs, sol_x)
diff_y = get_list_of_distances(ys, sol_y)
print("{:.8f}".format(calculate_distance(diff_x, diff_y)))
