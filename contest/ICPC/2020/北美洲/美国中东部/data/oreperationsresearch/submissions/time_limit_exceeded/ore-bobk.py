#!/usr/bin/python3

(nA, nB, nT) = map(int, input().split(' '))

aCap = map(int, input().split(' '))
bCap = map(int, input().split(' '))
tCap = map(int, input().split(' '))

aCap = list(aCap)
bCap = list(bCap)
tCap = list(tCap)

aSum = sum(aCap)
bSum = sum(bCap)

nCells = (nT+1) * nA * nB
cells = [False] * nCells

sourcePlane = 0
destPlane = 1

acceptable = "No"


def extEuclid(a, b):
    (oldr, r) = (a, b)
    (olds, s) = (1, 0)
    (oldt, t) = (0, 1)

    while r != 0:
        q = oldr // r
        (oldr, r) = (r, oldr - q * r)
        (olds, s) = (s, olds - q * s)
        (oldt, t) = (t, oldt - q * t)

    return oldr, olds, oldt


def isNNLinearCombination(n):

    # if n is not a multiple of gcd, then we can't do it
    if n % gcd != 0:
        return False

    # adjust... now, n = ax + by
    x = bzx * n // gcd
    y = bzy * n // gcd

    # the (very likely) potential issue... one of x and y is almost always < 0. Can't have that.
    # so, try to adjust to make both nonnegative

    if x < 0:
        # y must be positive
        # subtract out as much as possible from y while keeping it >= 0
        m = y // agcd
        y -= m * agcd
        # add the equivalent to x
        x += m * bgcd
    if y < 0:
        # x must be positive
        # subtract out as much as possible from x while keeping it >= 0
        m = x // bgcd
        x -= m * bgcd
        # add the equivalent to y
        y += m * agcd

    return x >= 0 and y >= 0


# we are trying to fill car t starting the A chain at a and the B chain at b.
# find all the A and B ending points where car t can be filled.
def fill_plane(a, b, t):
    # print('call ', a, b, t)
    global cells

    cLoc = nB * nA * destPlane
    partialA = 0
    for aa in range(nA):
        adjA = (a + aa) % nA
        cLoc1 = cLoc + nB * adjA
        partialB = 0
        for bb in range(nB):
            adjB = (b + bb) % nB
            if not cells[adjB + cLoc1]:
                # if n % gcd != 0:
                n = tCap[t] - partialA - partialB
                if n % gcd == 0:

                    # adjust... now, n = ax + by
                    x = bzx * n // gcd
                    y = bzy * n // gcd

                    # the (very likely) potential issue... one of x and y is almost always < 0. Can't have that.
                    # so, try to adjust to make both nonnegative

                    if x < 0:
                        # y must be positive
                        # subtract out as much as possible from y while keeping it >= 0
                        m = y // agcd
                        y -= m * agcd
                        # add the equivalent to x
                        x += m * bgcd
                    if y < 0:
                        # x must be positive
                        # subtract out as much as possible from x while keeping it >= 0
                        m = x // bgcd
                        x -= m * bgcd
                        # add the equivalent to y
                        y += m * agcd

                    if x >= 0 and y >= 0:
                        # if isNNLinearCombination(tCap[t] - partialA - partialB):
                        # if adjA == 0 and adjB == 8:
                        #     print(a, b, aa, bb, adjA, adjB, partialA, partialB, tCap[t], n, aSum, x, bSum, y)
                        # if adjA == 0 and adjB == 0:
                        #     print(a, b, aa, bb, adjA, adjB, partialA, partialB, tCap[t], n, aSum, x, bSum, y)
                        #     exit(0)
                        cells[adjB + cLoc1] = True
                        # return
            partialB += bCap[adjB]
        partialA += aCap[adjA]


(gcd, bzx, bzy) = extEuclid(aSum, bSum)
# a == agcd * g and b == bgcd * g...
# ... so, bgcd * a == agcd * b
agcd = aSum // gcd
bgcd = bSum // gcd

# fill the first car
fill_plane(0, 0, 0)

# try to fill the remaining cars
for tNum in range(1, nT):
    # flip the roles of the two planes
    #sourcePlane = 1 - sourcePlane
    #destPlane = 1 - destPlane
    sourcePlane += 1
    destPlane += 1

    # set the dest plane to all false
    # for rr in range(nA):
    #     for c in range(nB):
    #         cells[c + nB * (rr + nA * destPlane)] = False

    # scan the source plane for a valid ending point for the previous cars
    for rr in range(nA):
        for c in range(nB):
            # if we find an endpoint, try to fill the next car starting there
            if cells[c + nB * (rr + nA * sourcePlane)]:
                # fill_plane(rr, c, tNum)
                cLoc = nB * nA * destPlane
                partialA = 0
                for aa in range(nA):
                    adjA = (rr + aa) % nA
                    cLoc1 = cLoc + nB * adjA
                    partialB = 0
                    for bb in range(nB):
                        adjB = (c + bb) % nB
                        if not cells[adjB + cLoc1]:
                            # if n % gcd != 0:
                            n = tCap[tNum] - partialA - partialB
                            if n % gcd == 0:

                                # adjust... now, n = ax + by
                                x = bzx * n // gcd
                                y = bzy * n // gcd

                                # the (very likely) potential issue... one of x and y is almost always < 0. Can't have that.
                                # so, try to adjust to make both nonnegative

                                if x < 0:
                                    # y must be positive
                                    # subtract out as much as possible from y while keeping it >= 0
                                    m = y // agcd
                                    y -= m * agcd
                                    # add the equivalent to x
                                    x += m * bgcd
                                if y < 0:
                                    # x must be positive
                                    # subtract out as much as possible from x while keeping it >= 0
                                    m = x // bgcd
                                    x -= m * bgcd
                                    # add the equivalent to y
                                    y += m * agcd

                                if x >= 0 and y >= 0:
                                    # if isNNLinearCombination(tCap[t] - partialA - partialB):
                                    # if adjA == 0 and adjB == 8:
                                    #     print(a, b, aa, bb, adjA, adjB, partialA, partialB, tCap[t], n, aSum, x, bSum, y)
                                    # if adjA == 0 and adjB == 0:
                                    #     print(a, b, aa, bb, adjA, adjB, partialA, partialB, tCap[t], n, aSum, x, bSum, y)
                                    #     exit(0)
                                    cells[adjB + cLoc1] = True
                                    # return
                        partialB += bCap[adjB]
                    partialA += aCap[adjA]

    # for rr in range(nA):
    #     line = ''
    #     for c in range(nB):
    #         if cells[c + nB * (rr + nA * destPlane)]:
    #             line += '1'
    #         else:
    #             line += '.'
    #     print(line)
    # print('==========================================')

# scan the dest plane for any valid ending point. if found, we win
for rr in range(nA):
    for c in range(nB):
        if cells[c + nB * (rr + nA * destPlane)]:
            acceptable = "Yes"

print(acceptable)

exit(0)
