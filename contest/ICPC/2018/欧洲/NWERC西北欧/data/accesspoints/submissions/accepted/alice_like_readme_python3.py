#!/usr/bin/env python3
import sys
import itertools

def parse_input():
    n = int(input())
    xs, ys = [], []
    t = []
    for t in range(n):
        line = input()
        l = line.split(' ', 1)
        xs.append(l[0])
        ys.append(l[1])
    return list(map(int, xs)), list(map(int, ys))

def get_optimal_solution(ls):
    """ list of (count, position) """
    erg = []

    for i in ls:
        erg.append((1, i))
        while len(erg) > 1:
            last = erg.pop()
            prev = erg.pop()
            if prev[0] * last[1] < last[0] * prev[1]:
                num = last[0] + prev[0]
                su = last[1] + prev[1]
                erg.append((num, su))
            else:
                erg.append(prev)
                erg.append(last)
                break

    return map(lambda x: (x[0], float(x[1])/x[0]), erg)

def get_list_of_distances(ls, sol_l):
    erg = []
    i = 0
    for l in sol_l:
        for j in range(l[0]):
            yield l[1] - ls[i]
            i += 1

def calculate_distance(l_dx, l_dy):
    return sum(map(lambda x: x*x, l_dx)) +sum(map(lambda x: x*x, l_dy))

xs, ys = parse_input()
sol_x = get_optimal_solution(xs)
sol_y = get_optimal_solution(ys)
diff_x = get_list_of_distances(xs, sol_x)
diff_y = get_list_of_distances(ys, sol_y)
print("{:.8f}".format(calculate_distance(diff_x, diff_y)))
