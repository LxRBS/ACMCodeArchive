(n, e, b) = map(int, raw_input().split())
v = [None]*n
for i in map(int, raw_input().split()):
    v[i-1] = 0
v[0] = e % 2
for i in range(1, n):
    if v[i] is None: v[i] = v[i-1] ^ (e > 0)
    e -= (v[i] != v[i-1])
print ''.join(map(str, v))
