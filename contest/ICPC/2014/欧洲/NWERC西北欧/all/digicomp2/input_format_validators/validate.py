#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = '(0|-?[1-9]\d*)'
reswitchline = re.compile('[LR] ' + integer + ' ' + integer + '\n')

line = stdin.readline()
assert re.match(integer + ' ' + integer + '\n', line)
(ballcount, switchcount) = map(int, line.split())
assert 0 <= ballcount <= 10**18
assert 1 <= switchcount <= 5 * 10**5

inputs = [set() for i in range(switchcount+1)]
outputs = [()]
for i in range(switchcount):
    line = stdin.readline()
    assert reswitchline.match(line)
    (left, right) = map(int, line[2:].split())
    assert 0 <= left <= switchcount
    assert 0 <= right <= switchcount
    outputs.append((left, right))
    inputs[left].add(i+1)
    inputs[right].add(i+1)

# Start vertex has in-degree 0
assert len(inputs[1]) == 0

# Check for loops
q = {i for i in range(switchcount+1) if (len(inputs[i]) == 0)}
while len(q) != 0:
    k = q.pop()
    if k != 0:
        for o in outputs[k]:
            inputs[o].discard(k)
            if len(inputs[o]) == 0:
                q.add(o)
assert all((len(input) == 0 for input in inputs))

assert len(stdin.readline()) == 0
sys.exit(42)
