#!/usr/bin/python3

#
# f(p,b) = ...
#
# 1 + min_{x\in{1...k}}max(f(p-1,k-1),f(p,b-k)
#

(nBooks, nPallets) = map(int, input().split(' '))

cost = []
for r in range(nPallets+1):
    # cost.append([])
    # for c in range(nBooks+1):
    #     cost[r].append(0)
    cost.append([0]*(nBooks+1))

    cost[r][1] = 1

for c in range(1, nBooks+1):
    cost[1][c] = c

# for r in range(2, nPallets+1):
#     for c in range(2, nBooks+1):
r = 2
while r <= nPallets:
    c = 2
    while c <= nBooks:
        a = cost[r-1][0]
        b = cost[r][c-1]
        if a < b:
            a = b
        cost[r][c] = 1 + a
        # for k in range(2, c+1):
        k = 2
        while k <= c:
            a = cost[r-1][k-1]
            b = cost[r][c-k]
            if a < b:
                a = b
            t = 1 + a
            if t < cost[r][c]:
                cost[r][c] = t
            k += 1
        c += 1
    r += 1

# if minBooks == 0:
#    minBooks = 1

minBooks = None
maxBooks = None
for k in range(1, nBooks + 1):
    if 1 + max(cost[nPallets - 1][k - 1], cost[nPallets][nBooks - k]) == cost[nPallets][nBooks]:
        if minBooks is None:
            minBooks = k
            maxBooks = k
        else:
            maxBooks = k

if minBooks == maxBooks:
    print(cost[nPallets][nBooks], minBooks)
else:
    print(cost[nPallets][nBooks], '{}-{}'.format(str(minBooks), str(maxBooks)))
