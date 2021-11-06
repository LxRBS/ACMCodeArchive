import heapq

(A, B) = map(int, raw_input().split())
(n, m) = map(int, raw_input().split())
n += 1
adj = [[] for _ in range(n)]
radj = [[] for _ in range(n)]
for _ in range(m):
    (u, v, t) = map(int, raw_input().split())
    adj[u].append((v, t))
    radj[v].append((u, t))

def sssp(s, adj, dst):
    dst[s] = 0
    Q = [(0, s)]
    while Q:
        (d, u) = heapq.heappop(Q)
        if d > dst[u]: continue
        for (v, t) in adj[u]:
            if d + t < dst[v]:
                dst[v] = d+t
                heapq.heappush(Q, (d+t, v))

def poss(delay):
    useful = [False]*n
    for u in range(n):
        if src_dist[u] + dst_dist[u] <= A + delay and dst_dist[u] <= delay:
            useful[u] = True
    Q = [x for x in range(n) if useful[x]]
    indeg = [0]*n
    sub = [[] for _ in range(n)]
    while Q:
        u = Q.pop()
        for (v, t) in adj[u]:
            if dst_dist[v] + t <= delay:
                sub[u].append((v, t))
                indeg[v] += 1
                if not useful[v]:
                    useful[v] = True
                    Q.append(v)
    order = []
    Q = [x for x in range(n) if useful[x] and indeg[x] == 0]
    while Q:
        u = Q.pop()
        order.append(u)
        for (v, _) in sub[u]:
            indeg[v] -= 1
            if indeg[v] == 0: Q.append(v)
    if len(order) < sum(useful): return True
    latest = [A + delay - dst_dist[u] for u in range(n)]
    for u in order:
        # oops: should be >= B
        if latest[u] + dst_dist[u] > B:
            return True
        for (v, t) in sub[u]:
            latest[v] = max(latest[v], latest[u] + t)
    return False

src_dist = [(1<<50)]*n
dst_dist = [(1<<50)]*n
sssp(1, adj, src_dist)
sssp(n-1, radj, dst_dist)

lo = -1
hi = min(dst_dist[1], B - A)
if dst_dist[1] >= B:
    print dst_dist[1] - A
else:
    while hi - lo > 1:
        m = (lo+hi)/2
        if poss(m): hi = m
        else: lo = m
    print hi
