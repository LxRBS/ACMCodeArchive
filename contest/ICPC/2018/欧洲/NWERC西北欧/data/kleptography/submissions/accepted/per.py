(n, m) = map(int, raw_input().split())
a = [0]*(m-n) + [ord(i) - ord('a') for i in raw_input()]
c = [ord(i) - ord('a') for i in raw_input()]
k = [0]*m

for i in range(m-1, -1, -1):
    k[i] = (c[i]-a[i]) % 26
    if i-n >= 0: a[i-n] = k[i]

print ''.join(chr(x+ord('a')) for x in a)
