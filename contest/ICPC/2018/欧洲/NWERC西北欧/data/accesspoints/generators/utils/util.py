#!/usr/bin/env pypy

def read_input():
    # returns [(x1, y1), (x2, y2), ...]
    N = int(raw_input())
    erg = []
    for i in range(N):
        x, y = map(int, raw_input().split())
        erg.append((x, y))
    return erg

def print_testcase(output):
    # given [(x1, y1), (x2, y2), ...], prints
    # N
    # x1 y1
    # x2 y2
    # ...
    print(len(output))
    for o in output:
        print("{} {}".format(*o))
