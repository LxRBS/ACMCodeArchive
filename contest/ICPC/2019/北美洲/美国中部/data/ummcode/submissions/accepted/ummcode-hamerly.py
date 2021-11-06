#!/usr/bin/env python3

import sys
import string

L = set(string.ascii_letters).__contains__
letters = lambda s: ''.join(filter(L, s))
is_umm = lambda s: set(s) <= {'u', 'm'}
msg = ''.join(filter(is_umm, map(letters, sys.stdin.readline().split())))
msg = ''.join(['01'[c == 'u'] for c in msg])
print(''.join(chr(int(msg[i:i+7],2)) for i in range(0, len(msg), 7)))

