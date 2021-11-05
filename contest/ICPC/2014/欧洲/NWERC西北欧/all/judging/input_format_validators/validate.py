#! /usr/bin/env python2
import sys

n = int(sys.stdin.readline())

assert 1 <= n <= 100000

for i in range(n*2):
    s = sys.stdin.readline()
    assert s[-1] == '\n'
    s = s[:-1]
    assert 5 <= len(s) <= 15
    for c in s:
        assert 'a' <= c <= 'z'

assert(len(sys.stdin.readline()) == 0)
sys.exit(42)
