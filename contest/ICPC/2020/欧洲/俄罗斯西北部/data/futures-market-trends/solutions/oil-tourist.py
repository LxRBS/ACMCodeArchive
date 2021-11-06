from math import sqrt

st = input().split()
n = int(st[0])
c = float(st[1])
a = list(map(int, input().split()))

d = []
for i in range(n - 1):
  d.append(a[i + 1] - a[i])

pos = 0
neg = 0
for i in range(len(d)):
  s = 0
  sq = 0
  for j in range(i, len(d)):
    s += d[j]
    sq += d[j] * d[j]
    ln = j - i + 1
    if ln == 1:
      continue
    avg = s / ln
    std = sqrt((sq + ln * avg * avg - 2 * s * avg) / ln)
    if (std == 0 and avg > 0) or (std != 0 and avg / std >= c):
      pos += 1
    if (std == 0 and avg < 0) or (std != 0 and avg / std <= -c):
      neg += 1
print(pos, neg)
    
  