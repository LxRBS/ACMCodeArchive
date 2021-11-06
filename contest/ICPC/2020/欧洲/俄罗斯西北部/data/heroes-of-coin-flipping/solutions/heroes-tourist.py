k, m = map(int, input().split())

pn2 = [1.0 / (2 ** i) for i in range(k + 1)]

d = {}
by_level = [[] for _ in range(k)]
ans = 0

for i in range(m):
  si, mi = map(int, input().split())
  si -= 1
  mi -= 1
  by_level[si].append(mi)
  d[(si, mi)] = 1
  ans += 1
  for level in range(si + 1, k):
    mi //= 2
    if (level, mi) in d:
      ans -= pn2[level - si - 1]
      break

for lst in by_level:
  lst.sort()

free = [2 ** i for i in range(k)]
into = [0      for i in range(k)]

for level in range(k - 1, -1, -1):
  ptr = [0 for _ in range(k)]
  for val in by_level[level]:
    mi = val
    found = False
    for x in range(level + 1, k):
      mi //= 2
      while ptr[x] < len(by_level[x]) and by_level[x][ptr[x]] < mi:
        ptr[x] += 1
      if ptr[x] < len(by_level[x]) and by_level[x][ptr[x]] == mi:
        for y in range(0, level + 1):
          into[y + (x - level - 1)] -= 2 ** y
        found = True
        break
    if not found:
      for y in range(0, level + 1):
        free[y + (k - level - 1)] -= 2 ** y
    for y in range(0, level):
      into[y] += 2 ** (y + 1)

for i in range(k):
  for j in range(i):
    ans += free[i] * (1 - pn2[j]) / ((j + 1) * (j + 2))
  ans += free[i] * 1 / (i + 1)

for i in range(k):
  for j in range(i):
    ans += into[i] * (1 - pn2[j]) / ((j + 1) * (j + 2))
  ans += into[i] * (1 - pn2[i]) / (i + 1)

print(ans)
