import numpy as np
import random

MAX_N = 1000

# seed our random generators, we want the same cases each time
random.seed(4231337)
np.random.seed(4231337)

def write_case(name, parents, shuffle = False):
    n = len(parents)
    perm = np.arange(1,n+1)
    if shuffle:
        perm = np.random.permutation(perm)
    lines = []
    for i in range(n):
        if parents[i] == -1:
            continue
        lines.append(str(perm[parents[i]]) + ' ' + str(perm[i]))
    if shuffle:
        lines = np.random.permutation(lines)
    with open('secret/' + name + '.in', 'w') as f:
        f.write(str(n) + '\n')
        for line in lines:
            f.write(line + '\n')

def random_case(name):
    n = random.randint(2, MAX_N)
    parents = np.empty(n, dtype=np.int)
    parents[0] = -1
    for i in range(1, n):
        parents[i] = random.randint(0, i - 1) # pick on of the existing nodes as parent
    write_case(name, parents, True)

# linear
parents = np.arange(-1, MAX_N-1)
write_case('01-linear', parents, False)
write_case('02-linear-shuffle', parents, True)

# Fully balanced
parents = np.array([-1 if i == 0 else (i - 1) / 2 for i in range(MAX_N)])
write_case('03-binary-balanced', parents, False)
write_case('04-binary-balanced-shuffle', parents, True)

# Max branching
parents = np.array([-1 if i == 0 else 0 for i in range(MAX_N)])
write_case('05-max-branch', parents, False)
write_case('06-max-branch-shuffle', parents, True)

# Skewed binary, i.e. linear with an extra leaf attached to each internal node
parents = np.array([-1 if i == 0 else ((i - 1) / 2) * 2 for i in range(MAX_N)])
write_case('07-skewed-binary', parents, False)
write_case('08-skewed-binary-shuffle', parents, True)

# Smallest case
parents = np.array([-1,0])
write_case('09-smallest', parents, False)

# 10-almost-linear generated in some other way

# Some random cases
for i in range(11, 20):
    random_case(str(i) + '-random')

# Wide and deep at the same time
parents = np.array([-1 if i == 0 else (i - 1 if i * 2 < MAX_N else 0) for i in range(MAX_N)])
write_case('20-wide-and-deep', parents, False)
write_case('21-wide-and-deep-shuffle', parents, True)

# k-ary trees, i.e. each node has k children
parents = np.array([-1 if i == 0 else (i - 1) // 100 for i in range(MAX_N)])
write_case('22-100-ary', parents, False)
write_case('23-100-ary-shuffle', parents, True)
parents = np.array([-1 if i == 0 else (i - 1) // 30 for i in range(MAX_N)])
write_case('24-30-ary', parents, False)
write_case('25-30-ary-shuffle', parents, True)
parents = np.array([-1 if i == 0 else (i - 1) // 10 for i in range(MAX_N)])
write_case('26-10-ary', parents, False)
write_case('27-10-ary-shuffle', parents, True)
parents = np.array([-1 if i == 0 else (i - 1) // 3 for i in range(MAX_N)])
write_case('28-ternary', parents, False)
write_case('29-ternary-shuffle', parents, True)
