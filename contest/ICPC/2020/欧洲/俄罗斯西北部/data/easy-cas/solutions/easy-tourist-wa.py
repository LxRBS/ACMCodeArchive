import collections, sys, threading
sys.setrecursionlimit(10**9)
threading.stack_size(10**8)
 
def solve():
  n, init = map(int, input().split())
  a = []
  b = []
  s = []
  for i in range(n):
    x, y, z = map(int, input().split())
    a.append(x)
    b.append(y)
    s.append(z)

  bad_from_init = []
  bad_from_elsewhere = []
  e = {}
  for i in range(n):
    if s[i] == 1:
      if a[i] in e:
        e[a[i]].append(i)
      else:
        e[a[i]] = [i]
    else:
      if a[i] == init:
        bad_from_init.append(i + 1)
      else:
        bad_from_elsewhere.append(i + 1)

  order = []
  used = [False for _ in range(n)]

  def dfs(v):
    if not v in e:
      return
    while True:
      while len(e[v]) > 0 and used[e[v][-1]]:
        e[v].pop()
      if len(e[v]) > 0:
        eid = e[v][-1]
        used[eid] = True
        to = a[eid] ^ b[eid] ^ v
        dfs(to)
        order.append(eid)
      else:
        break

  dfs(init)

  ret = bad_from_elsewhere
  val = init
  for eid in order[::-1]:
    if val != a[eid]:
      print('No')
      exit()
    val = b[eid]
    ret.append(eid + 1)
    if val != init:
      for x in bad_from_init:
        ret.append(x)
      bad_from_init = []
  if len(bad_from_init) > 0:
    print('No')
    exit()

  print('Yes')
  print(' '.join(map(str, ret)))

threading.Thread(target=solve).start()
