#!/usr/bin/python3

# ===================================================================
#


def hungarian(N):

    # print('begin hungarian')
    # print(M)

    nn = len(N)

    M = []

    maxM = 0
    minM = 999999999
    for i in range(nn):
        M.append([])
        for j in range(nn):
            if N[i][j] < minM:
                minM = N[i][j]
            if N[i][j] > maxM:
                maxM = N[i][j]

    for i in range(nn):
        for j in range(nn):
#            M[i][j] = maxM + 1 - M[i][j]
            M[i].append(maxM - N[i][j])

    for i in range(nn):
        for j in range(nn):
            M[i][j] = minM + M[i][j]

    x = []
    for r in range(nn):
        x.append([False]*nn)

    ss = [False] * nn
    st = [False] * nn

    v = [0] * nn
    p = [999999999] * nn
    ls = [-1] * nn
    lt = [-2] * nn
    a = [-1] * nn

    f = 0
    for i in range(nn):
        for j in range(nn):
            if M[i][j] > f:
                f = M[i][j]

    u = [f] * nn

    while True:
        f = -1
        for i in range(nn):
            if ls[i] != -2 and not ss[i]:
                f = i
                break

        if f != -1:
            ss[f] = True
            for j in range(nn):
                if (not x[f][j]) and u[f] + v[j] - M[f][j] < p[j]:
                    lt[j] = f
                    p[j] = u[f] + v[j] - M[f][j]
        else:
            for i in range(nn):
                if lt[i] != -2 and (not st[i]) and p[i] == 0:
                    f = i
                    break

            if f == -1:
                d1 = 999999999
                d2 = 999999999

                for i in u:
                    if i < d1:
                        d1 = i

                for i in p:
                    if 0 < i < d2:
                        d2 = i

                d = min(d1, d2)

                for i in range(nn):
                    if ls[i] != -2:
                        u[i] -= d

                for i in range(nn):
                    if p[i] == 0:
                        v[i] += d
                    if p[i] > 0 and lt[i] != -2:
                        p[i] -= d

                if d2 >= d1:
                    break
            else:
                st[f] = True

                s = -1
                for i in range(nn):
                    if x[i][f]:
                        s = i
                        break

                if s == -1:
                    while True:
                        r = f
                        ll = lt[r]

                        if r >= 0 and ll >= 0:
                            x[ll][r] = not x[ll][r]
                        else:
                            break

                        r = ls[ll]
                        if r >= 0 and ll >= 0:
                            x[ll][r] = not x[ll][r]
                        else:
                            break

                        f = r

                    p = [999999999] * nn
                    lt = [-2] * nn
                    ls = [-2] * nn
                    ss = [False] * nn
                    st = [False] * nn

                    for i in range(nn):
                        ex = True
                        for j in range(nn):
                            ex = not x[i][j]
                            if not ex:
                                break
                        if ex:
                            ls[i] = -1
                else:
                    ls[s] = f

    for i in range(nn):
        for j in range(nn):
            if x[i][j]:
                a[i] = j

    #print('x:',x)

    for i in range(nn):
        for j in range(nn):
            M[i][j] = maxM - M[i][j]

    return a


#
# ===================================================================

n = int(input())

workerDist = []
mW = []
for workers in range(n):
    workerDist.append(list(map(int, input().split(' '))))
    mW.append([0]*n)

# print('workers')
# print(workerDist)

stationDist = []
mS = []
for stations in range(n):
    stationDist.append(list(map(int, input().split(' '))))
    mS.append([0]*n)

# print('stations')
# print(stationDist)

costList = []
bestCost = 999999999
bestW = []
bestS = []
bestGate = -1
for gate in range(0, n+1):
    for row in range(n):
        for col in range(n):
            if col < gate:
                mW[row][col] = workerDist[row][2*col]
                mS[row][col] = stationDist[row][2*col]
            else:
                mW[row][col] = workerDist[row][2*col+1]
                mS[row][col] = stationDist[row][2*col+1]
    #print('mW:',mW)
    wMatch = hungarian(mW)
    #print('wMatch:',wMatch)
    sMatch = hungarian(mS)
    # print(sMatch)

    cost = 0
    for row in range(n):
        cost += mW[row][wMatch[row]] + mS[row][sMatch[row]]

    costList.append(cost)

    if cost < bestCost:
        bestCost = cost
        bestW = wMatch
        bestS = sMatch
        bestGate = gate

nBest = 0
for ii in range(len(costList)):
    if costList[ii] == bestCost:
        nBest += 1

#if nBest != 1:
#    print('error')

#print('wMatch:',wMatch,bestW)
#print('sMatch:',sMatch,bestS)

print(bestCost)
for w in range(n):
    g = bestW[w]
    side = 'A'
    if g >= bestGate:
        side = 'B'
    for stn in range(n):
        if bestS[stn] == g:
            print('{} {}{} {}'.format(w+1, g+1, side, stn+1))
