def ints(line, i, j):
    res = []
    while i < j:
        k = i
        while line[k].isdigit(): k += 1
        if k > i: res.append(int(line[i:k]))
        i = k+1
    return res

def parse(line):
    res = []
    def add(L, b):
        if not b and res and res[-1][1] == 0:
            res[-1][0].extend(L)
        else:
            res.append((L, b))
    i = 0
    while i < len(line):
        if line[i] == '[':
            j = line.index(']', i)
            add(ints(line, i, j), 0)
            i = j
        elif line[i] == 's':
            b = line[i+1] == 'h'
            j = line.index(')', i) # oops: this assumes next right parenthesis matches the one for the current command
            sub = sorted(ints(line, i, j))
            if sub[0] == sub[-1]: b = 0
            add(sub, b)
            i = j
        i += 1
    return res

P1 = parse(raw_input())
P2 = parse(raw_input())
print '%sequal' % (['not ', ''][P1 == P2])
