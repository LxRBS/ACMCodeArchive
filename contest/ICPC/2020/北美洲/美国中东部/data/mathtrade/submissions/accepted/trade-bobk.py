#!/usr/bin/python3

names = []
items = []
next = []
seen = []

def nameInsert(name):
    for i in range(len(names)):
        if name == names[i]:
            return i
    names.append(name)
    next.append(-1)
    seen.append(False)
    return len(names) - 1

def hasInsert(item,who):
    for i in range(len(items)):
        if item == items[i][0]:
            items[i][1] = who
            return
    items.append([item,who,-1])

def wantsInsert(item,who):
    for i in range(len(items)):
        if item == items[i][0]:
            items[i][2] = who
            return
    items.append([item,-1,who])

n = int(input())

for i in range(n):
    (who,has,wants) = input().split(' ')
    j = nameInsert(who)
    hasInsert(has,j)
    wantsInsert(wants,j)

#print(names)
#print(items)

for item in items:
    if item[1] != -1 and item[2] != -1:
        next[item[1]] = item[2]

#print(next)

diam = 0
for i in range(len(names)):
    if seen[i]:
        continue
    start = i
    j = next[i]
    c = 1
    while j != -1 and j != start:
        c += 1
        j = next[j]
    if j == start and c > diam:
        diam = c

if diam == 0:
    print("no trades possible")
else:
    print(diam)
