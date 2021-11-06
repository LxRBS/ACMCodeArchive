#!/usr/bin/python3
import random
import sys

def t(d, n=50000, m=200000, shuffle=True):
	edges = []
	for i in range(n):
		for rng, prob in d.items():
			start, end = rng
			if start < 0:
				start += n + 1
			if end < 0:
				end += n + 1
			start += i
			end = min(i + end, n)
			length = end - start
			if length <= 0:
				continue
			js = random.sample(range(start, end), round(length * prob))
			for j in js:
				edges.append((i, j))
	output(edges, n, m, shuffle)

def output(edges, n, m, shuffle):
    perm = [i for i in range(n)]
    if shuffle:
        random.shuffle(edges)
        random.shuffle(perm)
    m = min(m, len(edges))
    edges = edges[:m]
    print(n, m)
    for u, v in edges:
        print(perm[u] + 1, perm[v] + 1)

command = ' '.join(sys.argv[1:])
random.seed('566' + command)
exec(command)
