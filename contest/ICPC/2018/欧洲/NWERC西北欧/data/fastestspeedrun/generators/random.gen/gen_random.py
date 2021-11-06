#!/usr/bin/env python3

import sys
import random

MAX_EDGE = 10**9

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

def gen_graph(n, strat):
    args = strat.split(',')
    strat, *args = args

    if strat == 'random':
        # Random parent pointers. Results in pretty terrible graphs (with
        # only ~log n components and cycle sizes ~sqrt n, I believe).
        return [random.randint(0, n) for _ in range(n)]

    if strat == 'chain':
        # Chain 0 <- 1 <- 2 <- ...
        return [i-1 for i in range(1, n+1)]

    if strat == 'almost-chain':
        # A long chain, with random stuff around it
        return [i-2 if i%2 == 0 and i < n//2 else max(0, min(n, i + random.randint(-3, 1))) for i in range(1, n+1)]

    if strat == 'chunks':
        # Nodes point within small clusters around themselves (requiring many
        # DP steps).
        size, = map(int, args)
        at = 0
        ret = []
        while at < n+1:
            s = min(random.randint(1, size), n+1 - at)
            ret.extend([random.randrange(at, at + s) for _ in range(s)])
            at += s
        return ret[1:]

    if strat == 'cycles':
        # ncyc cycles on n - noncyc levels, plus noncyc uniformly random levels
        ncyc, noncyc = map(int, args)
        n2 = n - noncyc
        assert 0 < ncyc <= n2
        splits = [0] + sorted(random.sample(range(1, n2), ncyc-1)) + [n2]
        sizes = [t - s for s, t in zip(splits, splits[1:])]
        assert len(sizes) == ncyc
        color = []
        for i in range(ncyc):
            color.extend([i] * sizes[i])
        color.extend([-1] * noncyc)
        assert len(color) == n
        random.shuffle(color)
        occ = [[] for _ in range(ncyc)]
        for i in range(n):
            if color[i] != -1:
                occ[color[i]].append(i)
        ret = [random.randint(0, n) for _ in range(n)]
        for li in occ:
            random.shuffle(li)
            for j in range(len(li)):
                ret[li[j]] = li[j-1] + 1
        return ret

    assert False, "Unknown graph strategy " + strat

def gen_mat(par, strat):
    n = len(par)
    if strat == 'random':
        # Completely random matrix, sorted row-wise. Optimal to jump directly
        # to last row or so.
        mat = []
        for _ in range(n):
            row = [random.randint(0, 890000) for _ in range(n+1)]
            row.sort(reverse=True)
            mat.append(row)
        return mat

    elif strat == 'fair':
        # Matrix where the cost to jump to a target is proportional to the gain
        # (including dependent levels), with a penalty factor for jumping too far,
        # and a bunch of noise.
        targets, oncyc = compute_targets(par)
        mat = []
        for i in range(1,n+1):
            t = targets[i]
            row = []
            for j in range(n+1):
                c = (t - j) * 800 + random.randint(-100, 800) + (min((t - j) ** 2 * 5, 50000) if j < t else 0)
                if oncyc[i]:
                    # For nodes on a cycle, it's fine to add a constant factor,
                    # since we're forced to pay it exactly once regardless.
                    # Let it vary a bit between nodes, but not too much so that
                    # we can't restrict to just the cheapest node.
                    c += 300000 + random.randint(0, 1000)
                row.append(max(c, 0))
            row.sort(reverse=True)
            mat.append(row)
        return mat

    elif strat == 'maximal':
        # Matrix where the cost to jump to a target is very close to the upper
        # limit of 10^9 to try and provoke issues with integer overflow.
        mat = []
        for _ in range(n):
            row = [random.randint(MAX_EDGE * 9 / 10, MAX_EDGE) for _ in range(n+1)]
            row.sort(reverse=True)
            mat.append(row)
        return mat

    elif strat == 'maxconst':
        mat = [[MAX_EDGE]*(n+1) for _ in range(n)]
        return mat

    assert False, "Unknown matrix strategy " + strat

def gen_pad(par, mat, pad, strat):
    n = len(par)
    pad -= n
    assert pad > 0

    if strat == 'after':
        # Add lots of levels that point to themselves, aren't more helpful
        # than our previous last level, and cost too much to get to unless
        # you progress to the previous last level and then beat them in order.
        inf = 0
        for li in mat:
            li += [li[-1]] * pad
            inf = max(inf, max(li) + 2)
        for i in range(pad):
            par.append(n+1 + i)
            mat.append([inf] * (n + i) + [1] * (pad - i + 1))
        return par, mat

    assert False, "Unknown padding strategy " + strat

def compute_targets(par):
    par = [0] + par
    orig_par = par
    n = len(par)
    jumps = [[par[i]] for i in range(n)]
    targets = [i for i in range(n)]
    assert n < 2**20
    for k in range(20):
        par2 = [None] * n
        for i in range(n):
            p = par[i]
            targets[p] = max(targets[p], targets[i])
            par2[i] = par[p]
        par = par2
    oncyc = [False] * n
    for i in range(n):
        oncyc[par[i]] = True
    return targets, oncyc

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
graph_strat = cmdlinearg('graph')
mat_strat = cmdlinearg('mat')
pad, pad_strat = cmdlinearg('pad', '0,').split(',')
pad = int(pad)
derandomize = bool(cmdlinearg('derandomize', 0))

par = gen_graph(n, graph_strat)
assert len(par) == n
assert 0 <= min(par) <= max(par) <= n
mat = gen_mat(par, mat_strat)

if pad != 0:
    par, mat = gen_pad(par, mat, pad, pad_strat)
    n = len(par)

print(n)
for i in range(n):
    li = mat[i]
    extra = 1 if derandomize else random.randint(1, min(10**5, MAX_EDGE - max(li)))
    assert all(li[i] >= li[i+1] for i in range(len(li)-1))
    print(par[i], extra, *[min(x + extra, MAX_EDGE) for x in li])
