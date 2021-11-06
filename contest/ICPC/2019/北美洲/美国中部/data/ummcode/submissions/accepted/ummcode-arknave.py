#!/usr/bin/env python3

import re

s = input()
words = s.split()

val = 0
cur_len = 0
res = []

for word in words:
    if all(c in 'um' or not c.isalnum() for c in word):
        for c in word:
            if c not in 'um':
                continue

            val <<= 1
            if c == 'u':
                val |= 1
            cur_len += 1

            if cur_len == 7:
                res.append(chr(val))
                val = 0
                cur_len = 0

print(''.join(res))
