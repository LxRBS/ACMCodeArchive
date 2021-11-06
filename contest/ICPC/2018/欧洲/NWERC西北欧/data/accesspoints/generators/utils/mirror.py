#!/usr/bin/env pypy
# mirror input, meaning that i will be changed to max(is) - i + 1

import util

poss = util.read_input()

xmax = max(map(lambda p: p[0], poss))
ymax = max(map(lambda p: p[1], poss))
poss = [(xmax - x + 1, ymax - y + 1) for x, y in poss]

util.print_testcase(poss)
