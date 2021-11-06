import math

eps_edge = 1e-6
eps_point = 1e-4

def diff(P1, P2):
    return (P2[0]-P1[0], P2[1]-P1[1])

def cross(P, Q):
    return Q[1]*P[0] - Q[0]*P[1]

def dot(P, Q):
    return Q[0]*P[0] + Q[1]*P[1]

def seg_pt_dist(P, dP, Q): # assumes |dP| = 1
    dPQ = diff(P, Q)
    return abs(cross(dP, dPQ)) if -eps_edge < dot(dP, dPQ) < 1+eps_edge else eps_point

def vertices_too_near(P1, P2):
    return math.hypot(*diff(P1, P2)) <= eps_point

def edges_too_near(P1, P2, Q1, Q2):
    dP = diff(P1, P2)
    dQ = diff(Q1, Q2)
    if min(seg_pt_dist(P1, dP, Q1), seg_pt_dist(P1, dP, Q2),
           seg_pt_dist(Q1, dQ, P1), seg_pt_dist(Q1, dQ, P2)) < eps_edge: return True
    dPQ = diff(P1, Q1)
    A = cross(dQ, dP)
    B = cross(dQ, dPQ)
    C = cross(dP, dPQ)
    if A < 0:
        A = -A
        B = -B
        C = -C
    return 0 <= B <= A and 0 <= C <= A


n = int(raw_input())

adj = [[] for _ in range(n)]
for _ in range(n-1):
    (u, v) = map(int, raw_input().split())
    adj[u-1].append(v-1)
    adj[v-1].append(u-1)

def draw(u, par, inv, pos):
    taken = set()
    for v in adj[u]:
        if v == par: continue
        for x in range(1000):
            if x in taken or x == inv: continue
            theta = x*2*math.pi/1000
            pos[v] = (pos[u][0] + math.cos(theta), pos[u][1] + math.sin(theta))
            ok = True
            for a in range(n):
                if pos[a] is None: continue
                if a != v and vertices_too_near(pos[v], pos[a]):
                    ok = False
                    break
                if a == u: continue
                for b in adj[a]:
                    if a < b and b != u and pos[b] is not None and edges_too_near(pos[a], pos[b], pos[u], pos[v]):
                        ok = False
                        break
                if not ok: break
            if ok:
                taken.add(x)
                break
        else:
            return False
        if not draw(v, u, (x+500) % 1000, pos):
            return False
    return True


for root in range(n):
    pos = [None]*n
    pos[root] = (0,0)
    if draw(root, -1, -1, pos): break

print '\n'.join('%.9f %.9f' % (x, y) for (x, y) in pos)
