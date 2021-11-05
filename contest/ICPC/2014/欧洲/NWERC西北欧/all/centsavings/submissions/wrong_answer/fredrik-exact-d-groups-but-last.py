import sys

(n, d) = (int(x) for x in sys.stdin.readline().split(' '))
costs = [int(x) for x in sys.stdin.readline().split(' ')]
assert(len(costs) == n)

totcosts = [costs[0]] + [1000000000 for x in range(d)]

for i in range(1,n):
    for j in range(d,0,-1):
        totcosts[j] = min(totcosts[j]+costs[i], int((totcosts[j-1]+costs[i]+5)/10)*10)
    totcosts[0] += costs[i]

print(int((totcosts[d]+5)/10)*10)
