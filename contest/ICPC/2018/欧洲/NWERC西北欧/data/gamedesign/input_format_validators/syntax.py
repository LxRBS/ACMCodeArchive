#!/usr/bin/env pypy
import sys

s = raw_input()
assert 1 <= len(s) <= 20

last_chr = ''
for i in s:
  assert last_chr != i
  assert i in 'LRUD'
  last_chr = i

sys.exit(42)
