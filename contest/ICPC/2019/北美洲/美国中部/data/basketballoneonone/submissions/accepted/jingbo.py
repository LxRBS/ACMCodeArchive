#!usr/bin/env python3

line = input()

n = len(line)
assert n % 2 == 0

def is_end(a, b):
    return max(a, b) >= 11 and abs(a - b) > 1

a, b = 0, 0
for i in range(0, n, 2):
    assert not is_end(a, b)

    player = line[i]
    score = int(line[i + 1])
    assert player in ['A', 'B']
    assert score in [1, 2]

    if player == 'A':
        a += score
    else:
        b += score

assert is_end(a, b)
if a > b:
    print('A')
else:
    print('B')
