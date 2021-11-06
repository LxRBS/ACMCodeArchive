import heapq

n = int(raw_input())
succ = [[] for _ in range(n)]
preds = [0]*n
e = [0]*n
avail = []
for i in range(n):
    line = map(int, raw_input().split())
    e[i] = line[0]
    for j in line[2:]:
        j -= 1
        succ[i].append(j)
        preds[j] += 1

for i in range(n):
    if not preds[i]: avail.append((e[i], i))

ans = 0
avail.sort()
for i in range(1, n+1):
    (eu, u) = heapq.heappop(avail)
    ans = max(ans, eu + n - i)
    for v in succ[u]:
        preds[v] -= 1
        if not preds[v]:
            heapq.heappush(avail, (e[v], v))

print ans
