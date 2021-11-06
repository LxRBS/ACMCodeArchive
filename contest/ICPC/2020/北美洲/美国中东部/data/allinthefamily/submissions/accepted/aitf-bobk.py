#!/usr/bin/python3

names = []
parents = []
counts = []

def insert(name):
    for i in range(len(names)):
        if name == names[i]:
            return i
    names.append(name)
    parents.append(-1)
    counts.append(0)
    return len(names) - 1

def suffix(n):
    if n % 10 == 0:
        return "th"
    elif n > 10 and n < 20:
        return "th"
    elif n % 10 == 1:
        return "st"
    elif n % 10 == 2:
        return "nd"
    elif n % 10 == 3:
        return "rd"
    else:
        return "th"

(t,p) = map(int,input().split(' '))

for i in range(t):
    line = input().split(' ')
    #print(line)
    par = insert(line[0])
    for j in range(2,len(line)):
        kid = insert(line[j])
        parents[kid] = par

#print(names)
#print(parents)

for i in range(p):
    (a,b) = input().split(' ')
    for j in range(len(names)):
        counts[j] = -1
    aPos = insert(a)
    count = 0
    while aPos != -1:
        counts[aPos] = count
        count += 1
        aPos = parents[aPos]

    bPos = insert(b)
    count = 0
    while bPos != -1 and counts[bPos] == -1:
        count += 1
        bPos = parents[bPos]

#    print(counts[bPos],count)

    if count == 0:
        if counts[bPos] == 1:
            print(a,"is the child of",b)
        else:
            print(a,"is the ",end='')
            for j in range(counts[bPos]-2):
                print("great ",end='')
            print("grandchild of",b)
    elif counts[bPos] == 0:
        if count == 1:
            print(b,"is the child of",a)
        else:
            print(b,"is the ",end='')
            for j in range(count-2):
                print("great ",end='')
            print("grandchild of",a)
    elif count == 1 and counts[bPos] == 1:
        print(a,"and",b,"are siblings")
    else:
        c = min(count,counts[bPos])
        r = max(count,counts[bPos]) - c
        c -= 1
        print(a,"and",b,"are",c,end='')
        suf = suffix(c)
        print(suf,"cousins",end='')
        if r > 0:
            print(',',r,"time",end='')
            if r > 1:
                print('s',end='')
            print(" removed",end='')
        print()
