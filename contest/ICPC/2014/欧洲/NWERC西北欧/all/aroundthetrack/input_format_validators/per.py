#!/usr/bin/python
from sys import stdin
import sys
import re
import math

NMAX = 50
CMAX = 5000
MAXCASES = 1

integer = "(0|-?[1-9]\d*)"

cases = 0

def diff(P1, P2):
    return (P2[0]-P1[0], P2[1]-P1[1])

def cross(P, Q):
    return Q[1]*P[0] - Q[0]*P[1]

def dot(P, Q):
    return P[0]*Q[0] + P[1]*Q[1]

def isect(P1, P2, Q1, Q2):
    dP = diff(P1, P2)
    dQ = diff(Q1, Q2)
    A = cross(dQ, dP)
    B = cross(dQ, diff(P1, Q1))
    C = cross(dP, diff(P1, Q1))
    if A < 0:
        A = -A
        B = -B
        C = -C
    if A == B == C == 0:
        PQ1 = dot(dP, diff(P1, Q1))
        PQ2 = dot(dP, diff(P1, Q2))
        return PQ1*PQ2 <= 0 or 0 <= PQ1 <= dot(dP, dP) or 0 <= PQ2 <= dot(dP, dP)
    return 0 <= B <= A and 0 <= C <= A

def angle(p, q):
    a = math.atan2(q[1], q[0])-math.atan2(p[1], p[0])
    if a < -math.pi: a += math.pi
    if a > math.pi: a -= math.pi
    return a

def inside(p, P):
    a = 0
    for i in range(len(P)):
        a += angle(diff(P[i], p), diff(P[(i+1)%len(P)], p))
    return abs(a) > math.pi/2

def area(P):
    a = 0
    for i in range(len(P)):
        a += cross(P[(i+1)%len(P)], P[i])
    return a/2

assert isect((4, 0), (10, 0), (8, -4), (8,4))
assert not isect((4, 0), (10, 0), (8, 2), (8,4))
assert not isect((4, 0), (7, 0), (8, -4), (8,4))
assert isect((5, 0), (10, 0), (15, 0), (7, 0))
assert not isect((5, 0), (10, 0), (15, 0), (27, 0))

def check_poly(P):
    # check no touching
    N = len(P)
    for i in range(N):
        for j in range(2,N-1):
            assert not isect(P[i], P[(i+1)%N], P[(i+j)%N], P[(i+j+1)%N])
    # check ccw
    A = 0
    for i in range(N):
        A += cross(P[i], P[(i+1)%N])
    assert A > 0

def read_poly():
    line = sys.stdin.readline()
    assert re.match(integer + "\n", line)
    N = int(line)
    assert 3 <= N <= NMAX

    P = []
    for i in range(N):
        line = sys.stdin.readline()
        assert re.match(integer + " " + integer + "\n", line)
        (x,y) = map(int, line.split())
        assert -CMAX <= x <= CMAX
        assert -CMAX <= y <= CMAX
        P.append((x,y))

    check_poly(P)
    return P


inner = read_poly()
outer = read_poly()
I = len(inner)
O = len(outer)
for i in range(I):
    for o in range(O):
        assert not isect(inner[i], inner[(i+1)%I], outer[o], outer[(o+1)%O])
# sufficient to check single point of inner since no isect with outer
assert inside(inner[0], outer)


assert len(stdin.readline()) == 0
sys.exit(42)
