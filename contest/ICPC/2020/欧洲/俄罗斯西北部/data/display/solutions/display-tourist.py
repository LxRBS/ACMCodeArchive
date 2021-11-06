n, w, h, s = map(int, input().split())
max_cnt = 0
best_c = ' '
for i in range(n):
  c = input()
  for _ in range(h):
    st = input()
    cnt = 0
    for j in range(w):
      if st[j] == '#' and (j == 0 or st[j - 1] == '.'):
        cnt += 1
    if cnt > max_cnt:
      max_cnt = cnt
      best_c = c
res = ''
while s > 0:
  res += best_c
  s -= 2 * max_cnt
print(res)
  