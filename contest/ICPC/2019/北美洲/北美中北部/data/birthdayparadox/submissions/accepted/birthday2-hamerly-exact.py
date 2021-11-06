#!/usr/bin/env python3

# compute the entire thing as a rational number, then convert it to a log
# probability at the end

import fractions
import math
import sys

DEBUG = 1 < len(sys.argv)

def factorial(x):
    f = 1
    for i in range(2, x+1):
        f *= i
    return f

def nchoosek(n, k):
    return factorial(n) // (factorial(n - k) * factorial(k))

def multinomial_norm(events):
    '''The normalization term for a multinomial distribution, defined as
        n! / prod(xi! for xi in events)
        where n = sum(events)'''
    n = factorial(sum(events))
    d = 1
    for e in events:
        d *= factorial(e)
    return n // d

def multinomial(events, possible_events):
    '''Log of the multinomial probability for a given event vector. We imagine
    that the number of possible_events is given, and make the strongly
    simplifying assumption that the probability of each event is equal.'''
    return fractions.Fraction(multinomial_norm(events), possible_events ** sum(events))

def num_orders(x):
    '''The number of ways that we can uniquely permute the values in x. If all
    are unique, then it is log(n!) (where n = len(x)). But if there are
    multiple copies of some value, then we divide by (subtract the log of) the
    number of ways of permuting that value (for all duplicated values).
    It turns out that this is exactly the multinomial normalization, so we use
    that.'''
    counter = [x.count(xi) for xi in set(x)]
    return multinomial_norm(counter)

def solve(x, k=365):
    m = multinomial(x, k)
    nk = nchoosek(k, len(x))
    no = num_orders(x)
    p = m * nk * no
    if DEBUG:
        print('m {}, nk {}, no {}, p {}'.format(m, nk, no, p))
    return min(p, 1)

def main():
    sys.stdin.readline()
    x = list(map(int, sys.stdin.readline().split()))
    p = solve(x)
    if DEBUG:
        print(p)
    lp = math.log(p.numerator) - math.log(p.denominator)
    print('{:0.15f}'.format(lp / math.log(10)))

def test(n, count):
    '''Brute-force test the probabilities with an array of length n and a sum
    of count.'''

    def _gen(x, remaining, i=0):
        '''Generate all arrays x where sum(x) == constant (initially
        the value of remaining).'''
        if i == len(x):
            if not remaining:
                yield x
        else:
            for j in range(remaining + 1):
                x[i] = j
                yield from _gen(x, remaining - j, i + 1)

    # enumerate all possible vectors with the given sum
    x = [0] * n
    total_probability = 0.0
    grouped_probabilities = {}
    for z in _gen(x, count):
        zt = tuple(sorted(filter(None, z)))
        if zt not in grouped_probabilities:
            grouped_probabilities[zt] = 0.0

        p = multinomial(x, n)
        grouped_probabilities[zt] += p
        total_probability += p

    # use our solution to compute the same values over all unique
    # representations of those vectors
    solution_total_probability = 0.0
    for z in sorted(grouped_probabilities):
        p = solve(z, n)
        solution_total_probability += p
        rel_diff = abs(p - grouped_probabilities[z]) / grouped_probabilities[z]
        if 1e-5 < rel_diff:
            print(z, grouped_probabilities[z], p, rel_diff)

    # compare results
    print('brute force total probability', total_probability)
    print('solution    total probability', solution_total_probability)

if __name__ == '__main__':
    main()
    #test(8, 9)
