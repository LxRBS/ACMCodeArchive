#!/usr/bin/env pypy

import random
import sys

MAX_M = 10 ** 5
MAX_WEIGHT = 20000

ri = random.randint

def solve_or_get_close(weights):
    '''Determine if the weights are a solvable instance; if so return True and
    the solution; if not, return False and a close guess'''

    multiplicity = {}
    for w in weights:
        multiplicity[w] = multiplicity.get(w, 0) + 1

    left_sum = 0
    total_sum = sum(weights)
    unique_weights = set(weights)
    last_weight = None
    for w in sorted(unique_weights):
        w_total_weight = w * multiplicity[w]
        if 2 * left_sum + w_total_weight == total_sum:
            return True, w
        elif (w + 1) not in unique_weights and 2 * left_sum + 2 * w_total_weight == total_sum:
            return True, w + 1
        elif 2 * left_sum > total_sum - w_total_weight:
            return False, last_weight

        last_weight = w
        left_sum += w_total_weight

    assert False # should not get here

def solveable(weights):
    '''convenience function'''
    s, _ = solve_or_get_close(weights)
    return s

def const_fn(c):
    '''create a function which always generates a constant value (of c)'''
    f = lambda *x: c
    return f

def gen_cases(name, m_generator, case_generator, stream):
    m = m_generator()
    print('{}: generating case with m = {}'.format(name, m))
    case = None
    while case is None or not solveable(case):
        case = case_generator(m)
        assert len(case) == m
    random.shuffle(case)
    stream.write('{}\n'.format(m))
    stream.write('{}\n'.format(' '.join(map(str, case))))

def gen_random(m):
    weights = sorted([random.randint(1, MAX_WEIGHT) for _ in range(m)])
    while True:
        s, t = solve_or_get_close(weights)
        if s:
            break

        smaller = [w for w in weights if w < t]
        larger  = [w for w in weights if t < w]
        equal   = [w for w in weights if w == t]

        diff = sum(larger) - sum(smaller)

        half = larger if 0 < diff else smaller
        i = random.choice(range(len(half)))
        newval = min(65535, max(1, half[i] - diff))
        diff -= half[i] - newval
        half[i] = newval

        weights = smaller + equal + larger

    return weights

if __name__ == '__main__':
    cases = {
            'all_max': (1, const_fn(MAX_M), const_fn([MAX_WEIGHT] * MAX_M)),
            'random-any-m': (10, lambda *x: ri(1, MAX_M), gen_random),
            'random-large-m': (10, lambda *x: ri(MAX_M - 1000, MAX_M), gen_random),
            }

    for casename in cases:
        num_cases, m_gen, case_gen = cases[casename]
        for casenum in range(num_cases):
            filename = '{}-{:02d}.in'.format(casename, casenum)
            with open(filename, 'w') as out:
                gen_cases(filename, m_gen, case_gen, out)
