n = int(input())
a = [0] + list(map(int, input().split()))
a.sort()
d = 0
for i in range(n):
  d = max(d, a[i + 1] - a[i])
for i in range(n - 1):
  if a[i + 2] - a[i] <= d:
    d = 0
    break
print(d)
