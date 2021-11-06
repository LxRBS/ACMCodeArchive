from sys import argv
from random import randrange as rr

MAXN = 450
MAXM = 1100
MAXK1K2 = 800
MAXK1 = 800
MAXW = 10**9


class Edge:
    def __init__(self, u, v, w):
        self.u = u
        self.v = v
        self.w = w

    def set_color(self, color):
        self.color = color


def random_tc():
    N = rr(MAXN//4, MAXN + 1)
    M = min(MAXM, rr(N, MAXM + 1))

    # create edge list
    edges = []
    # Default color = 0 for each edge
    for i in range(M):
        u = rr(1, N + 1)
        while True:
            v = rr(1, N + 1)
            if v != u:
                w = rr(1, MAXW + 1)
                e = Edge(u, v, w)
                edges.append(e)
                break

    # Assign colors to edges
    for edge in edges:
        random_color = rr(3)
        edge.set_color(random_color)

    src = rr(1, N + 1)
    dst = rr(1, N + 1)

    return N, M, edges, src, dst


def max_test():
    N = rr(MAXN//2, MAXN + 1)
    M = MAXM

    # create edge list
    edges = []
    # Default color = 0 for each edge
    for i in range(M):
        u = rr(1, N + 1)
        while True:
            v = rr(1, N + 1)
            if v != u:
                w = rr(5*10**7, MAXW + 1)
                e = Edge(u, v, w)
                edges.append(e)
                break

    # Assign colors to edges
    for edge in edges:
        random_color = rr(3)
        edge.set_color(random_color)

    src = rr(1, N + 1)
    dst = rr(1, N + 1)

    return N, M, edges, src, dst


def create_test_file(basepath, index, maxtest=False):
    with open("{0}/{1}.in".format(basepath, index), "w") as f:
        n, m, edges, s, t = max_test()
        k1 = rr(1, 3) if maxtest else rr(1, MAXK1//2)
        k2 = MAXK1K2//k1 if maxtest else rr(1, MAXK1K2 // k1)
        f.write("{0} {1} {2} {3}\n".format(n, m, k1, k2))
        for edge in edges:
            f.write("{0} {1} {2} {3}\n".format(edge.u, edge.v, edge.w, edge.color))
        f.write("{0} {1}\n".format(s, t))


basepath = argv[1]
cnt_files = int(argv[2])
max_test_cnt = int(argv[3])
for i in range(1, cnt_files + 1):
    create_test_file(basepath, i, maxtest=False)
for i in range(1 + cnt_files, 1 + cnt_files + max_test_cnt):
    create_test_file(basepath, i, maxtest=True)
