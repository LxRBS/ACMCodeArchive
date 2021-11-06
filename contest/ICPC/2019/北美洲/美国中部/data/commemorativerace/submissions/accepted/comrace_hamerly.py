#!/usr/bin/env python2

# direct translation from minpath_hamerly.cpp

import sys

UNVISITED = None
BEING_VISITED = 1
VISITED = 2

def dfs_rec(edges, current, state, finish):
    '''Recursive DFS -- correct but tends to overflow
    stack'''
    if state.get(current):
        return

    state[current] = BEING_VISITED

    for dest in edges[current]:
        dfs_rec(edges, dest, state, finish)
    
    state[current] = VISITED
    finish.append(current)

def dfs_nonrec(edges, current, state, finish):
    '''Iterative DFS -- hard to get correct; works on DAGs
    but not cyclic graphs.'''
    if state.get(current):
        return

    state[current] = BEING_VISITED
    stack = [(current, False)]
    while stack:
        current, done = stack.pop()

        if state[current] == VISITED:
            continue
        
        if done:
            state[current] = VISITED
            finish.append(current)
        else:
            stack.append((current, True))
            for dest in edges[current]:
                if state.get(dest) != VISITED:
                    state[dest] = BEING_VISITED
                    stack.append((dest, False))

def longest_paths(g, dfs_alg=dfs_nonrec):
    path_length = [0] * len(g)
    multiplicity = [1] * len(g)
    finish = []
    state = {}
    for start in range(len(g)):
        dfs_alg(g, start, state, finish)

    for u in reversed(finish):
        for v in g[u]:
            l = path_length[u] + 1
            if path_length[v] < l:
                path_length[v] = l
                multiplicity[v] = multiplicity[u]
            elif path_length[v] == l:
                multiplicity[v] += multiplicity[u]

    return path_length, multiplicity, finish

def main():
    n, m = tuple(map(int, sys.stdin.readline().split()))

    fwd_edges = [[] for _ in range(n)]
    rev_edges = [[] for _ in range(n)]

    for _ in range(m):
        u, v = tuple(map(int, sys.stdin.readline().split()))
        fwd_edges[u-1].append(v-1)
        rev_edges[v-1].append(u-1)

    fwd_path_length, fwd_multiplicity, fwd_finish = longest_paths(fwd_edges)
    rev_path_length, rev_multiplicity, rev_finish = longest_paths(rev_edges)

    longest_path_length = max(fwd_path_length)

    longest_path_multiplicity = 0
    multiplicity = [0] * n
    path_length = [0] * n
    for u in range(n):
        multiplicity[u] = fwd_multiplicity[u] * rev_multiplicity[u]
        path_length[u] = fwd_path_length[u] + rev_path_length[u]
        if rev_path_length[u] == longest_path_length:
            longest_path_multiplicity += rev_multiplicity[u]

    answer = longest_path_length
    for u in reversed(fwd_finish):
        if path_length[u] != longest_path_length or multiplicity[u] != longest_path_multiplicity:
            continue

        critical_v = -1
        for v in fwd_edges[u]:
            if path_length[v] == longest_path_length and multiplicity[v] == longest_path_multiplicity and fwd_path_length[u] + 1 == fwd_path_length[v]:
                critical_v = v
                break
        if critical_v == -1:
            continue

        max_length_through_u = fwd_path_length[u]
        for v in fwd_edges[u]:
            if v != critical_v:
                max_length_through_u = max(max_length_through_u, fwd_path_length[u] + rev_path_length[v] + 1)
        answer = min(answer, max_length_through_u)

    print(answer)

if __name__ == '__main__':
    main()

