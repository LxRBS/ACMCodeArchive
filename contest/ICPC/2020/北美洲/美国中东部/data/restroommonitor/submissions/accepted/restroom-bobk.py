#!/usr/bin/python3

(s,n) = map(int,input().split(' '))

tpNo = []
tpYes = [1000000001]

for i in range(n):
    (d,t) = input().split(' ')
    d = int(d)

    if t == 'y':
        tpYes.append(d)
    else:
        tpNo.append(d)

tpNo.sort()
tpYes.sort()

#print(tpNo)
#print(tpYes)

okay = "Yes"

# try to schedule tp usage

i = len(tpYes) - 1
t = tpYes[i]
while i >= 0:
    # move t down to current deadline if necessary
    if tpYes[i] < t:
        t = tpYes[i]
    # schedule current user
    tpYes[i] = t
    # go back in time
    t -= 1
    # next user
    i -= 1

#print(tpYes)

# if first tp user is scheduled before now, can't schedule
if tpYes[0] < 1:
    okay = "No"

# now, try to schedule everyone else

t = 1
nextTp = 0
start = 0

while start < len(tpNo):
    end = start + s
    if t == tpYes[nextTp]:
        end -= 1
        nextTp += 1
    if end > len(tpNo):
        end = len(tpNo)
    for i in range(start,end):
        if tpNo[i] < t:
            okay = "No"
    start = end
    t += 1

print(okay)
