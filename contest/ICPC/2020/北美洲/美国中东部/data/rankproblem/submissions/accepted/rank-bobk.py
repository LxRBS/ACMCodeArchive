#!/usr/bin/python3

(n, m) = map(int, input().split(' '))

ranking = []
for i in range(n):
  ranking.append(i+1)
  
for i in range(m):
  (ti,tj) = input().split(' ')
  ti = int(ti[1:])
  tj = int(tj[1:])
  
  for p in range(n):
    if ranking[p] == ti:
      pi = p
    if ranking[p] == tj:
      pj = p
  
  if pj < pi:
    tmp = ranking[pj]
    for p in range(pj,pi):
      ranking[p] = ranking[p+1]
    ranking[pi] = tmp
    
for i in range(n):
  ranking[i] = 'T' + str(ranking[i])

out = ' '.join(ranking)

print(out)

