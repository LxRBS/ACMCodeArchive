import random

def ints(line, i, j):
    res = []
    while i < j:
        k = i
        while line[k].isdigit(): k += 1
        if k > i: res.append(int(line[i:k]))
        i = k+1
    return res

def match(line, i):
    d = 1
    for j in range(i, len(line)):
        d += ('()'.find(line[j])-1)%3 - 1
        if not d: return j

def parse(line):
    res = []
    shuffled_length = 0
    def add(L, b):
        if b: random.shuffle(L)
        res.extend(L)
    i = 0
    while i < len(line):
        if line[i] == '[':
            j = line.index(']', i)
            add(ints(line, i, j), 0)
            i = j
        elif line[i] == 's':
            b = line[i+1] == 'h'
            j = match(line, i+7+b)
            sub = sorted(ints(line, i, j))
            if b and sub[0] != sub[-1]: shuffled_length += len(sub)
            add(sub, b)
            i = j
        i += 1
    return res + [shuffled_length]

random.seed(2018)
P1 = parse(raw_input())
random.seed(2018)
P2 = parse(raw_input())

print '%sequal' % (['not ', ''][P1 == P2])
