import heapq

n = int(raw_input())
ans = 0

cost = [[0]*(n+1) for _ in range(n+1)]
back = [0]*(n+1)

for i in range(1,n+1):
    line = map(int, raw_input().split())
    (x, t) = line[:2]
    ans += t
    for j in range(n+1):
        cost[j][i] = line[2+j] - t
    cost[x][i] = 0
    back[i] = x

state = [0]*(n+1)
for i in range(1, n+1):
    at = i
    while not state[at]:
        state[at] = i
        at = back[at]
    if state[at] != i: continue
    cycle = []
    while state[at] == i:
        cycle.append(at)
        state[at] = -1
        at = back[at]
    mincost = min(cost[n][u] for u in cycle)
    ans += mincost
    for u in cycle:
        for v in range(n+1):
            cost[v][u] = max(0, cost[v][u] - mincost)

dst = [0] + [1<<30]*n
done = [False]*(n+1)
for _ in range(n+1):
    x = -1
    for u in range(n+1):
        if not done[u] and (x == -1 or dst[u] < dst[x]):
            x = u
    done[x] = True
    for u in range(n+1):
        dst[u] = min(dst[u], dst[x] + cost[x][u])

print ans + dst[n]
