#!/usr/bin/env python
def cost(z):
    st = []
    for i in range(n):
        st.append([z[i], 1])
        while len(st) > 1 and st[-1][0]*st[-2][1] < st[-2][0]*st[-1][1]:
            st[-2][0] += st[-1][0]
            st[-2][1] += st[-1][1]
            st.pop()
    x = []
    for (a, f) in st: x.extend([1.0*a/f]*f)
    return sum((x[i]-z[i])**2 for i in range(n))

n = int(raw_input())
(X, Y) = zip(*[map(int, raw_input().split()) for _ in range(n)])
print cost(X) + cost(Y)
