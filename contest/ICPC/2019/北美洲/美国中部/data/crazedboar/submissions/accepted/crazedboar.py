#!/usr/bin/env python3
''' 
ANH
deal with branch cut by noting each arc that crosses it:
    All such arcs must overlap, so only need to remember extremes
    on either side, include arcs to or from cut.
order these and remaining arcs (low angle, high angle)  
note overlapping sequences, add range for each overlapping seq.

Three cases for arc from single tree:
   tree beyond range:  ignore
   hit tree at max range
   past tree at max range (see where graze against tree)

'''
import sys
from math import sqrt, asin, acos, atan2, pi, tau

data = list(map(int, sys.stdin.read().split()))
d = data.pop()
R = data.pop()
d2 = d*d
data.reverse()
n = data.pop() # ignore
arcs = []
nCross = -pi # eliminate -pi to nCross from tree across cut + others so far
pCross = pi  # eliminate hCross to pi from tree across cut + others so far
while data:
    x = data.pop()
    y = data.pop()
    rR = data.pop() + R
    D2= x*x + y*y
    D = sqrt(D2)
    if d+rR <= D: # never reach tree
        continue
    A = atan2(y, x) # mid of arc
    if D2 <= rR*rR + d2: # goes past: find grazing angle
        th = asin(rR/D)
    else: # find angle where hits tree
        th = acos((D2 + d2 - rR*rR)/(2*d*D))
    if A - th <= -pi: # crosses cut, center negative
        nCross = max(nCross, A + th)
        pCross = min(pCross, A - th + tau)
    elif A + th >= pi: # crosses cut, center positive
        nCross = max(nCross, A + th - tau)
        pCross = min(pCross, A - th)
    else:
        arcs.append((A-th, A+th))
arcs.append((-pi, nCross))
arcs.append((pCross, pi))
arcs.sort()
tot = 0 # culumative angles where hit a tree
lseq = hseq = -pi # 0 length, most negative
for l, h in arcs:
    if l > hseq:
        tot += hseq - lseq
        lseq = l
        hseq = h
    elif h > hseq:
        hseq = h
tot += hseq - lseq # get last seq
print(1 - tot/tau)
