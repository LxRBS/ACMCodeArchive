import sys
t = int(input())
for _ in range(t):
  n = int(input())

  f1 = list(range(2, n + 1)) + [1]
  print('?', ' '.join(map(str, f1)))
  sys.stdout.flush()
  g1 = list(map(int, input().split()))

  f2 = [1] + list(range(3, n + 1)) + [2]
  print('?', ' '.join(map(str, f2)))
  sys.stdout.flush()
  g2 = list(map(int, input().split()))

  start = -1
  for i in range(n):
    if g2[i] == i + 1:
      start = i + 1
      break

  p = [-1] * (n + 1)
  p[1] = start
  for i in range(1, n):
    p[i + 1] = g1[p[i] - 1]
  print('!', ' '.join(map(str, p[1:])))
  sys.stdout.flush()
