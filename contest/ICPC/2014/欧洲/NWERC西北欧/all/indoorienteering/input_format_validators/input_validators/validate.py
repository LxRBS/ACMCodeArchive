#! /usr/bin/env python2
import sys

(n, len) = (int(x) for x in sys.stdin.readline().split(' '))
d = [[int(x) for x in line.split()] for line in sys.stdin]

assert 2 <= n <= 14
assert 1 <= len <= 10**15

for i in range(n):
    assert d[i][i] == 0
    for j in range(n):
        assert d[i][j] == d[j][i]
        if i != j:
            assert 1 <= d[i][j] <= len
        for k in range(n):
            assert d[i][j] <= d[i][k] + d[k][j]

sys.exit(42)
