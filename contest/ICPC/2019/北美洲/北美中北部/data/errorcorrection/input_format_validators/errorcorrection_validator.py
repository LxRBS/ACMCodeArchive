#!/usr/bin/env python3

import re
import sys

MAX_N = 500

line = sys.stdin.readline()
print(repr(line))
assert re.match('^[1-9][0-9]*\n$', line)
n = int(line)
assert 1 <= n <= MAX_N
words = [sys.stdin.readline() for _ in range(n)]
pattern = re.compile('^[a-z]+\n$')
assert all(map(pattern.match, words))
assert len(words) == n == len(set(words))

s = set(words[0])
assert len(s) == len(words[0])
for w in words:
    assert s == set(w)

assert not sys.stdin.readline()

sys.exit(42)

