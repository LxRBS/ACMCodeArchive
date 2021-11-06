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

print('+' + ' ' * cnt + '+')
for x in range(2 ** cnt):
  if not val[x]:
    print('|' + ' ' * cnt + '|')
    print('+' + ''.join([chars[i] if (x & (1 << i)) == 0 else '-' for i in range(cnt)]) + '+')
    