#!/usr/bin/env python3
import itertools
s = input().replace('xor', '^')
letters = {c for c in s.replace('and', '').replace('or', '').replace('not', '') if c.isalpha()}
print('+' + ' ' * len(letters) + '+')
for mask in itertools.product([0, 1], repeat=len(letters)):
	d = dict(zip(letters, mask))
	if eval(s, d):
		continue
	print('|' + ' ' * len(letters) + '|')
	print('+', end='')
	for x in letters:
		print('-' if d[x] else x, end='')
	print('+')
