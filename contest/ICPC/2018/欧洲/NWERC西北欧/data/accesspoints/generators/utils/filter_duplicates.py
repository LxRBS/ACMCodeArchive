#!/usr/bin/env pypy
import util

def linearize(x, y):
    return x * 1232456789 + y

poss = util.read_input()

seen = set()
newposs = []
for pos in poss:
    v = linearize(*pos)
    if v not in seen:
        newposs.append(pos)
        seen.add(v)


util.print_testcase(newposs)
