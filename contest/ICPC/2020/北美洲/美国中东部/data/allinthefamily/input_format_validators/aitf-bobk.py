#!/usr/bin/python3

leftSide = []
people = []
parent = []
children = []
color = []
pNum = -1
nEdges = 0

def dfs(v,par):
    global color

    color[v] = 1

    for c in children[v]:
        if par is not None and par == c:
            continue
        if color[c] == 1:
            print('Error: cycle in graph')
            exit(1)
        elif color[c] == 0:
            dfs(c,v)

    color[v] = 2

try:
    (t, p) = map(int, input().split(' '))
except EOFError:
    print('Error: out of data')
    exit(1)
except ValueError:
    print('Error: Improper data')
    exit(1)

if (0 < t < 100) == False:
    print('Error: bad t =',t)
    exit(1)

if (0 < p <= 1000) == False:
    print('Error: bad p =',p)
    exit(1)

for i in range(t):
    try:
        line = input().split(' ')
    except EOFError:
        print('Error: out of data')
        exit(1)
    if line[0] in leftSide:
    	print('Error:',line[0],'appears as parent twice')
    	exit(1)
    leftSide.append(line[0])
    if line[0] not in people:
        pNum = len(people)
        people.append(line[0])
        parent.append(None)
        children.append([])
        color.append(0)
    else:
        pNum = people.index(line[0])

    try:
        d = int(line[1])
    except ValueError:
        print('Error: Improper data')
        exit(1)
    except IndexError:
        print('Error: Improper data length')

    nEdges += d

    kids = line[2:]
    if len(kids) != d:
        print('Error: Number of children !=',d)
        exit(1)

    for k in kids:
        if k in people:
            kNum = people.index(k)
            if parent[kNum] is not None:
                print('Error:',k,'has multiple parents')
                exit(1)
            parent[kNum] = pNum
        else:
            kNum = len(people)
            people.append(k)
            parent.append(pNum)
            children.append([])
            color.append(0)
        children[pNum].append(kNum)

for i in range(p):
    try:
        (s1,s2) = input().split(' ')
    except EOFError:
        print('Error: Out of data')
        exit(1)

    if s1 not in people or s2 not in people:
        print('Error:',s1,'or',s2,'not in tree')
        print('People:',people)
        exit(1)

    if s1 == s2:
        print('Error: Same name')

try:
    line = input()
    print('Error: extra data')
    exit(1)
except EOFError:
    pass

if nEdges != len(people) - 1:
    print('Error: Invalid edge count')
    exit(1)

if len(people) > 100:
    print('Error: Too many people',len(people))
    exit(1)

foundRoot = False
for i in range(len(people)):
    if parent[i] is None:
        if foundRoot:
            print('Error: Multiple roots')
            exit(1)
        foundRoot = True
    else:
        children[i].append(parent[i])

dfs(0,None)

for i in range(len(people)):
    if color[i] != 2:
        print('Error: disconnected graph')
        exit(1)

exit(42)
