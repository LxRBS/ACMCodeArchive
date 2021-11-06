#!/usr/bin/env python3
import sys, os, random

random.seed(hash('naq19'))

if os.listdir():
    print('Error: directory not empty')
    sys.exit(1)

MAX_N = 100000
MAX_T = 1000
MAX_W = 1000

class TestCase(object):
    def __init__(self, taxes, edges, expected=None):
        self.taxes = taxes
        self.edges = edges
        assert len(taxes) == len(edges) + 1

        self.ans = self.solve()
        if expected is not None:
            assert self.ans == expected

    def solve(self):
        n = len(self.taxes)
        tree = [[] for _ in range(n)]
        for u, v, w in self.edges:
            tree[u].append((v, w))
            tree[v].append((u, w))

        preorder = []
        par = [-1 for _ in range(n)]
        depth = [0 for _ in range(n)]
        stk = [(0, -1)]
        while stk:
            u, p = stk.pop()
            preorder.append(u)
            for v, w in tree[u]:
                if v == p:
                    continue
                par[v] = u
                depth[v] = depth[u] + w
                stk.append((v, u))

        sizes = [1 for _ in range(n)]
        tax_sums = list(self.taxes)
        for u in reversed(preorder):
            for v, w in tree[u]:
                if v == par[u]:
                    continue

                sizes[u] += sizes[v]
                tax_sums[u] += tax_sums[v]

        sum_dist = sum(depth)
        sum_tax_dist = sum(self.taxes[u] * depth[u] for u in range(n))
        stk = [(0, sum_dist, sum_tax_dist)]
        ans = [0 for _ in range(n)]
        while stk:
            u, a, b = stk.pop()
            ans[u] = (b + self.taxes[u] * a)
            for v, w in tree[u]:
                if v == par[u]:
                    continue
                na = a - w * sizes[v] + w * (n - sizes[v])
                nb = b - w * tax_sums[v] + w * (tax_sums[0] - tax_sums[v])
                stk.append((v, na, nb))

        return ans

    def in_lines(self):
        return ['{}'.format(len(self.taxes)), ' '.join(str(x) for x in self.taxes)] + ['{} {} {}'.format(u + 1, v + 1, w) for u, v, w in self.edges]

    def out_lines(self):
        return [str(x) for x in self.ans]

test_num = 0
def write_test(base_path, tc, name='', force_name=''):
    if not os.path.exists(base_path):
        os.makedirs(base_path)
    global test_num

    name = ('{:02d}'.format(test_num)) + ('_' + name if name else '')
    if force_name:
        name = force_name

    fn_in = os.path.join(base_path, name + '.in')
    with open(fn_in, 'w') as f_in:
        f_in.write(''.join(map(lambda x: x + '\n', tc.in_lines())))
    fn_ans = os.path.join(base_path, name + '.ans')
    with open(fn_ans, 'w') as f_ans:
        f_ans.write(''.join(map(lambda x: x + '\n', tc.out_lines())))
    test_num += 1

def sample_1():
    taxes = [2, 5, 3, 4, 1]
    edges = [(0, 1, 2), (1, 3, 5), (3, 2, 3), (4, 1, 6)]
    return TestCase(taxes, edges)

def sample_2():
    taxes = [4, 3, 3, 4, 3, 3]
    edges = [(0, 2, 2), (1, 0, 1), (0, 3, 6), (3, 4, 6), (5, 3, 2)]
    return TestCase(taxes, edges)

def hand_1():
    taxes = [5, 3, 1, 4, 2, 9]
    edges = [(0, 1, 4), (0, 2, 5), (1, 3, 3), (1, 4, 2), (2, 5, 1)]

    return TestCase(taxes, edges)

def star(n):
    taxes = [random.randint(1, MAX_T) for _ in range(n)]
    labels = list(range(n))
    random.shuffle(labels)
    edges = [(labels[0], labels[i], random.randint(1, MAX_W)) for i in range(1, n)]
    random.shuffle(edges)

    return TestCase(taxes, edges)

def linked_list(n, w = None):
    taxes = [random.randint(1, MAX_T) for _ in range(n)]
    labels = list(range(n))
    random.shuffle(labels)
    edges = [(labels[i - 1], labels[i], random.randint(1, MAX_W) if w is None else w) for i in range(1, n)]
    random.shuffle(edges)

    return TestCase(taxes, edges)

def width_tree(n, width):
    order = list(range(n))
    random.shuffle(order)
    edges = []
    for i in range(1, n):
        parent = (i - 1) // width
        w = random.randint(1, MAX_W)
        edges.append((order[parent], order[i], w))

    random.shuffle(edges)

    taxes = [random.randint(1, MAX_T) for _ in range(n)]
    return TestCase(taxes, edges)

write_test('sample', sample_1(), 'sample_1', '1')
write_test('sample', sample_2(), 'sample_2', '2')

write_test('secret', hand_1(), 'hand_1')
for n in [20, 2000, MAX_N]:
    write_test('secret', star(n), 'star_' + str(n))
    write_test('secret', linked_list(n), 'linked_list_' + str(n))

for w in [2, 100]:
    write_test('secret', width_tree(MAX_N, 2), 'tree_width{}_{}'.format(w, MAX_N))

write_test('secret', linked_list(MAX_N, MAX_W), 'max_linked_list')
