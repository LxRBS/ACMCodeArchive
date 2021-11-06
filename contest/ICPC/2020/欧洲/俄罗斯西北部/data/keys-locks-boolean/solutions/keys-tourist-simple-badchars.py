st = input()

cnt = 8
val = []
for mask in range(2 ** cnt):
  for idx in range(cnt):
    ch = chr(ord('a') + idx)
    if (mask & (2 ** idx)) != 0:
      exec(ch + ' = True')
    else:
      exec(ch + ' = False')
  val.append(eval(st))

for x in range(2 ** cnt):
  for y in range(2 ** cnt):
    if val[x] and not val[y] and (x & y) == x:
      print('IMPOSSIBLE')
      exit()

print('+' + ' ' * cnt + '+')
for x in range(2 ** cnt):
  if not val[x]:
    print('|' + ' ' * cnt + '|')
    print('+' + ''.join([chr(ord('a') + i) if (x & (1 << i)) == 0 else '-' for i in range(cnt)]) + '+')
    