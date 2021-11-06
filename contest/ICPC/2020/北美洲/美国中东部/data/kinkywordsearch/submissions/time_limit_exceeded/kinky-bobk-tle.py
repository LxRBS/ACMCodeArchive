#!/usr/bin/python3

dR = [-1,-1,-1,0,1,1,1,0]
dC = [-1,0,1,1,1,0,-1,-1]

(r,c) = map(int,input().split(' '))

grid = []
for i in range(r):
    grid.append(input().split(' '))

k = int(input())

match = list(input())

acceptable = "NO"

#print(match)

q = []

for i in range(r):
    for j in range(c):
        if grid[i][j] == match[0]:
            q.append((1,-1,-1,i,j))

while len(q) > 0:
#    print(q)
    token = q.pop(0)
    if token[0] == len(match):
        if token[1] == k:
            acceptable = "YES"
    else:
        for d in range(8):
            i2 = token[3] + dR[d]
            j2 = token[4] + dC[d]
            if i2 >= 0 and i2 < r and j2 >= 0 and j2 < c and grid[i2][j2] == match[token[0]]:
                nk = token[1]
                if token[2] != d:
                    nk += 1
                q.append((token[0]+1,nk,d,i2,j2))

print(acceptable)
