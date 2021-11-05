import sys

(n, d) = (int(x) for x in sys.stdin.readline().split(' '))
costs = [int(x) for x in sys.stdin.readline().split(' ')]
assert(len(costs) == n)

totcosts = [0] + [1000000000 for x in range(d)]

for i in range(n):
    totcosts[0] += costs[i]
    for j in range(1,d+1):
        totcosts[j] = min(totcosts[j]+costs[i], int((totcosts[j-1]+5)/10)*10)

print(int((totcosts[d]+5)/10)*10)
