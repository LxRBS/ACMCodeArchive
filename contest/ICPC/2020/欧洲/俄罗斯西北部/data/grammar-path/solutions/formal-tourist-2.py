import sys

p = int(input())
single = []
double = []
for i in range(p):
  s = input().split()
  if len(s[2]) == 1:
    single.append((s[0], s[2]))
  else:
    double.append((s[0], s[2]))

n, m, st, fin = map(int, input().split())
st -= 1
fin -= 1
d = [[[0 for c in range(26)] for j in range(n)] for i in range(n)]
for i in range(m):
  x, y, c = input().split()
  x = int(x) - 1
  y = int(y) - 1
  for prod in single:
    if prod[1] == c:
      d[x][y][ord(prod[0][0]) - ord('A')] = 1

init = ord('S') - ord('A')
changed = True
res = 0
while changed:
  changed = False
  if d[st][fin][init] != 0:
    res = d[st][fin][init]
  for prod in double:
    A = ord(prod[0][0]) - ord('A')
    B = ord(prod[1][0]) - ord('A')
    C = ord(prod[1][1]) - ord('A')
    for i in range(n):
      for j in range(n):
        if d[i][j][B] != 0:
          for k in range(n):
            if d[j][k][C] != 0:
              ft = d[i][j][B] + d[j][k][C]
              if res > 0 and ft >= res:
                continue
              if d[i][k][A] == 0 or ft < d[i][k][A]:
                d[i][k][A] = ft
                changed = True

if res == 0:
  print('NO')
else:
  print(res)
