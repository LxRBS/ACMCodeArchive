#!/usr/bin/env pypy
import random
import util

SIZE_SUBSEQUENCE = 100000

poss = util.read_input()

newposs = []
for i in range(0, len(poss), SIZE_SUBSEQUENCE):
    cur = poss[i:i+SIZE_SUBSEQUENCE]
    cur_x = map(lambda x: x[0], cur)
    cur_y = map(lambda x: x[1], cur)
    random.shuffle(cur_x)
    random.shuffle(cur_y)
    newposs.extend(zip(cur_x, cur_y))

util.print_testcase(newposs)
