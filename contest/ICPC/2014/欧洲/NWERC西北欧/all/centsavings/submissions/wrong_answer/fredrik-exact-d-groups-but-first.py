import sys

(n, d) = (int(x) for x in sys.stdin.readline().split(' '))
costs = [int(x) for x in sys.stdin.readline().split(' ')]
assert(len(costs) == n)

totcosts = [0] + [1000000000 for x in range(d)]

for i in range(n):
    for j in range(d,0,-1):
        totcosts[j] = min(totcosts[j], int((totcosts[j-1]+5)/10)*10)+costs[i]
    totcosts[0] += costs[i]

print(int((totcosts[d]+5)/10)*10)
