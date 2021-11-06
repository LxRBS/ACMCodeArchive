st = input()

chars_d = {}
for i in range(len(st)):
  if 'a' <= st[i] <= 'z':
    if i == 0 or not ('a' <= st[i - 1] <= 'z'):
      if i == len(st) - 1 or not ('a' <= st[i + 1] <= 'z'):
        chars_d[st[i]] = 1
chars = list(chars_d)

cnt = len(chars)
val = []
for mask in range(2 ** cnt):
  for idx in range(cnt):
    if (mask & (2 ** idx)) != 0:
      exec(chars[idx] + ' = True')
    else:
      exec(chars[idx] + ' = False')
  val.append(eval(st))

for x in range(2 ** cnt):
  for y in range(2 ** cnt):
    if val[x] and not val[y] and (x & y) == x:
      print('IMPOSSIBLE')
      exit()

H = 40
W = 50
grid = [[' ' for j in range(W)] for i in range(H)]
grid[0][0] = '+'
grid[0][W - 1] = '+'
for i in range(1, H - 1):
  grid[i][W - 1] = '|'
grid[H - 1][W - 1] = '+'
grid[H - 1][0] = '+'
for j in range(1, W - 1):
  grid[H - 1][j] = '-'
grid[0][W - 3] = '+'
for j in range(1, W - 3):
  grid[0][j] = '-'

row = 0
col = 0
for x in range(2 ** cnt):
  if not val[x]:
    important = True
    for y in range(2 ** cnt):
      if y > x and (x & y) == x and not val[y]:
        important = False
        break
    if not important:
      continue
    if row == 0 or row >= H - 4:
      if row > 0:
        col += cnt + 3
      grid[0][col] = '+'
      grid[H - 3][col] = '+'
      for i in range(1, H - 3):
        grid[i][col] = '|'
      grid[2][col + cnt + 1] = '+'
      grid[H - 1][col + cnt + 1] = '+'
      for i in range(3, H - 1):
        grid[i][col + cnt + 1] = '|'
      row = 0
    row += 2
    grid[row][col] = '+'
    grid[row][col + cnt + 1] = '+'
    for i in range(cnt):
      if (x & (1 << i)) == 0:
        grid[row][col + i + 1] = chars[i]
      else:
        grid[row][col + i + 1] = '-'
#    print('|' + ' ' * cnt + '|')
 #   print('+' + ''.join([chars[i] if (x & (1 << i)) == 0 else '-' for i in range(cnt)]) + '+')

for s in grid:
  print(''.join(s))
