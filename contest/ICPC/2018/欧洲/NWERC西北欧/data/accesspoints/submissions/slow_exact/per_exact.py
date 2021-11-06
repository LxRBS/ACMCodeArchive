#!/usr/bin/env python

# Exact solution using fractions, for producing the answer files.
#
# Much slower than the other solutions and does not represent
# something a team should do in practice so we don't care if it gets
# AC or TLE.

from fractions import Fraction

def cost(z):
    st = []
    for i in range(n):
        st.append([z[i], 1])
        while len(st) > 1 and st[-1][0]*st[-2][1] < st[-2][0]*st[-1][1]:
            st[-2][0] += st[-1][0]
            st[-2][1] += st[-1][1]
            st.pop()
    x = []
    for (a, f) in st: x.extend([Fraction(a, f)]*f)
    return sum((x[i]-z[i])**2 for i in range(n))

def frac_to_str(x):
    from decimal import getcontext, Decimal
    getcontext().prec = 20
    return str(Decimal(x.numerator) / Decimal(x.denominator))

n = int(raw_input())
(X, Y) = zip(*[map(int, raw_input().split()) for _ in range(n)])
print frac_to_str(cost(X) + cost(Y))
