#!/usr/bin/env python3
import itertools
s = input().replace('xor', '^')
letters = {c for c in s.replace('and', '').replace('or', '').replace('not', '') if c.isalpha()}
ans = ['+' + ' ' * len(letters) + '+']
masks = set()
for mask in itertools.product([0, 1], repeat=len(letters)):
	d = dict(zip(letters, mask))
	if eval(s, d):
		continue
	masks.add(mask)
	for i in range(len(mask)):
		prev = list(mask)
		prev[i] = 0
		if tuple(prev) not in masks:
			print('IMPOSSIBLE')
			exit()
	ans.append('|' + ' ' * len(letters) + '|')
	ans.append('+' + ''.join([('-' if d[x] else x) for x in letters]) + '+')
print('\n'.join(ans))
