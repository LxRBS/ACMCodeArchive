n, k = map(int, input().split())
C = [[0 for j in range(n + 1)] for i in range(n + 1)]
for i in range(n + 1):
  C[i][0] = 1
  for j in range(1, i + 1):
    C[i][j] = C[i - 1][j] + C[i - 1][j - 1]

def count(x):
  ret = C[n][x]
  if n % 2 == 0:
    if x % 2 == 0:
      ret += C[n // 2][x // 2]
  else:
    ret += C[n // 2][x // 2]
  assert ret % 2 == 0
  return ret // 2

ans = 0
for x in range(n + 1):
  y = k - x
  if y < 0 or y > k or y > x:
    continue
  ans += count(x) + count(y)
print(ans)