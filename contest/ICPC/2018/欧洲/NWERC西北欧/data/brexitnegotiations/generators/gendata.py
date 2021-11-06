import os
import random
import sys

MAX_N = 4*10**5
MAX_M = 4*10**5
MAX_E = 10**6

CASE = 10
DEST = os.path.join(os.getcwd(), '../data/secret')
SHUFFLE_DATA = True

def next_file(short_desc=None, long_desc=None):
    global CASE
    basename = os.path.join(DEST, '%02d' % CASE)
    CASE += 1
    if short_desc is not None:
        basename += '-' + short_desc
    if long_desc is not None:
        with open(basename+'.desc', 'w') as desc_out:
            desc_out.write(long_desc)
    return open(basename+'.in', 'w')

def save_case(topics, short_desc=None, long_desc=None, shuffle_adj_list=True):
    n = len(topics)
    sys.stderr.write('save_case n %d shortdesc %s\n' % (n, short_desc))
    for i in range(n):
        for j in topics[i][1]: assert i > j
    names = range(1, n+1)
    if SHUFFLE_DATA:
        random.shuffle(names)
    invnames = [0]*(n+1)
    for i in range(n):
        invnames[names[i]-1] = i
    f = next_file(short_desc, long_desc)
    f.write('%d\n' % n)
    for i in range(n):
        (e, L) = topics[invnames[i]]
        if SHUFFLE_DATA and shuffle_adj_list:
            random.shuffle(L)
        if L:
            f.write('%d %d %s\n' % (e, len(L), ' '.join(map(str, [names[x] for x in L]))))
        else:
            f.write('%d 0\n' % (e))
    f.close()

def uniform_adjusted_cost(n):
    return [random.randint(n, MAX_E) - i for i in range(n)]

def decreasing_adjusted_cost(n):
    return [2*(n-i) for i in range(n)]

def almost_constant_adjusted_cost(n):
    pos = random.randint(0, n-1)
    return [4711+n-i+(i==pos) for i in range(n)]

COST_GENERATORS = [uniform_adjusted_cost, decreasing_adjusted_cost, almost_constant_adjusted_cost]

def random_dag(n, m):
    print 'gen random dag n %d m %d' % (n, m)
    seen = set()
    dag = [[] for _ in range(n)]
    V = range(n)
    for _ in range(m):
        while True:
            a, b = sorted(random.sample(V, 2))
            if (a, b) not in seen:
                break
        seen.add((a, b))
        dag[b].append(a)
    return dag

def subset(n, m):
    BITS = range((n-1).bit_length())
    seen = set()
    dag = [[] for _ in range(n)]
    for _ in range(m):
        iters = 0
        while True:
            a = random.randint(0, n-1)
            free = [i for i in BITS if ~a & (1<<i)]
            if not free: continue
            bit = random.choice(free)
            b = a | (1<<bit)
            if b < n and (a,b) not in seen:
                break
            iters += 1
            if iters > 10000: return dag
        assert b > a
        seen.add((a, b))
        dag[b].append(a)
    return dag

def divisibility(n, m): # m only upper bound, if lattice has more edges then random subset returned
    is_prime = [True]*(n+2)
    primes = []
    for p in range(2, n+2):
        if is_prime[p]:
            primes.append(p)
            q = p*p
            while q < n+2:
                is_prime[q] = False
                q += p
    edges = []
    for i in range(2, n+2):
        for p in primes:
            if i*p >= n+2: break
            edges.append((i-2, i*p-2))
    print 'gen divisibility lattice n %d m %d (e avail %d)' % (n, m, len(edges))
    if len(edges) > m:
        random.shuffle(edges)
        edges = edges[:m]
    dag = [[] for _ in range(n)]
    for (a, b) in edges:
        assert b > a
        dag[b].append(a)
    return dag

def complete(n, m): # m ignored
    return [range(i) for i in range(n)]

def chain(n, m): # m ignored
    dag = [[] for _ in range(n)]
    for i in range(n-1):
        dag[i+1].append(i)
    return dag

def bipartite_chain(n, m): # m ignored
    assert n % 2 == 0
    dag = [[] for _ in range(n)]
    for i in range(0, n/2):
        dag[n/2+i].append(i)
        dag[n/2 + (i+1) % (n/2)].append(i)
    return dag

def two_paths_same_source(n, m): # m ignored
    dag = [[] for _ in range(n)]
    dag[1].append(0)
    dag[2].append(0)
    for i in range(3, n): dag[i].append(i-2)
    return dag

def two_paths_same_sink(n, m): # m ignored
    dag = [[] for _ in range(n)]
    dag[n-1].append(n-3)
    dag[n-1].append(n-2)
    for i in range(n-3): dag[i+2].append(i)
    return dag

def two_paths_same_ends(n, m): # m ignored
    dag = [[] for _ in range(n)]
    dag[1].append(0)
    dag[2].append(0)
    dag[n-1].append(n-3)
    dag[n-1].append(n-2)
    for i in range(3,n-1): dag[i].append(i-2)
    return dag

def star(n, m): # m ignored
    dag = [[] for _ in range(n)]
    for i in range(n-2, -1, -1):
        dag[n-1].append(i)
    return dag

def half_star(n, m):
    dag = [[] for _ in range(n)]
    for i in range(n/2):
        dag[n-1].append(i)
    return dag

DAG_GENERATORS = [random_dag, subset, divisibility]

def gen_case(n, m, cost_gen, graph_gen, short_desc=None, shuffle_adj_list=True):
    save_case(zip(cost_gen(n), graph_gen(n, m)),
              short_desc=short_desc, shuffle_adj_list=shuffle_adj_list)


def main():
    random.seed(13)

    global CASE
    # leave room for any hand-crafted small cases
    CASE = 20

    save_case([(23, [])], short_desc='minimal')

    for _ in range(10):
        n = random.randint(1, 20)
        m = random.randint(0, min(MAX_M, n*(n-1)/2))
        cost_gen = random.choice(COST_GENERATORS)
        dag_gen = random.choice(DAG_GENERATORS)
        gen_case(n, m, cost_gen, dag_gen, short_desc='small_random')

    random.seed(23)

    # leave room for the larger hand-crafted cases
    CASE = 40
    n = 1
    while (n+1)*n/2 <= MAX_M: n += 1
    gen_case(n, n*(n-1)/2, uniform_adjusted_cost, complete, short_desc='complete')

    gen_case(MAX_N, 0, uniform_adjusted_cost, random_dag, short_desc='empty')

    gen_case(MAX_N, MAX_M, uniform_adjusted_cost, two_paths_same_source, short_desc='two_paths_same_source')
    gen_case(MAX_N, MAX_M, uniform_adjusted_cost, two_paths_same_sink, short_desc='two_paths_same_sink')
    gen_case(MAX_N, MAX_M, uniform_adjusted_cost, two_paths_same_ends, short_desc='two_paths_same_ends')

    gen_case(MAX_N, MAX_M, uniform_adjusted_cost, bipartite_chain, short_desc='bipartite')

    gen_case(MAX_N, MAX_M,
             lambda n: [1]*(n-1) + [MAX_E],
             lambda n, m: [[] for _ in range(n-1)] + [range(n-1)],
             short_desc='star_maxanswer')

    gen_case(MAX_N, MAX_M, uniform_adjusted_cost, half_star, short_desc='half_star_uniform_costs')

    gen_case(MAX_N, MAX_M, decreasing_adjusted_cost, half_star, short_desc='half_star_decreasing_costs')

    gen_case(MAX_N, MAX_M, decreasing_adjusted_cost, star, short_desc='star_decreasing_costs', shuffle_adj_list=False)

    gen_case(MAX_N, MAX_M, uniform_adjusted_cost, star, short_desc='star_uniform_costs')

    gen_case(MAX_N, MAX_M,
              uniform_adjusted_cost,
              random_dag, short_desc='max_random')
    gen_case(MAX_N, MAX_M,
              uniform_adjusted_cost,
              divisibility, short_desc='max_divisibility_lattice')
    gen_case(MAX_N, MAX_M,
              decreasing_adjusted_cost,
              random_dag, short_desc='max_decreasing_costs')
    gen_case(MAX_N, MAX_M,
              almost_constant_adjusted_cost,
              chain, short_desc='chain_almost_constant_costs')

    for _ in range(10):
        n = random.randint(1, MAX_N)
        m = random.randint(0, min(MAX_M, n*(n-1)/2))
        cost_gen = random.choice(COST_GENERATORS)
        dag_gen = random.choice(DAG_GENERATORS)
        gen_case(n, m, cost_gen, dag_gen, short_desc='random')


if __name__=='__main__':
    main()
