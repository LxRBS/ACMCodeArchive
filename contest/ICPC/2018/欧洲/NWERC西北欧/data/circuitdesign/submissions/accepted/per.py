import cmath

n = int(raw_input())
adj = [[] for _ in range(n)]
for _ in range(n-1):
    (u, v) = map(int, raw_input().split())
    adj[u-1].append(v-1)
    adj[v-1].append(u-1)

def dfs(u, par, sz):
    sz[u] = 1
    for v in adj[u]:
        if v != par:
            dfs(v, u, sz)
            sz[u] += sz[v]

def draw(u, par, lo, rng, sz):
    dt = rng/sz[u]
    for v in adj[u]:
        if v != par:
            pos[v] = pos[u] + cmath.rect(1, lo + sz[v]*dt/2)
            draw(v, u, lo, sz[v]*dt, sz)
            lo += sz[v]*dt

pos = [0j]*n
sz = [0]*n
dfs(0, -1, sz)
draw(0, -1, 0.0, min(6.28, 0.5*sz[0]), sz)

print '\n'.join('%.9f %.9f' % (p.real, p.imag) for p in pos)
