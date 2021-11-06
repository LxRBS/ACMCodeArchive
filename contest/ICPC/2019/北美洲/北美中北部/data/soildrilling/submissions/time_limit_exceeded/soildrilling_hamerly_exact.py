#!/usr/bin/env python2

# This version does all computations with rational numbers until taking a
# square-root at the end. No epsilon calculations needed.

from __future__ import division

import fractions
import math
import sys

class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def dot(self, other): return self.x * other.x + self.y * other.y
    def __sub__(self, other): return Point(self.x - other.x, self.y - other.y)
    def __add__(self, other): return Point(self.x + other.x, self.y + other.y)
    def __mul__(self, other): return Point(self.x * other, self.y * other)
    def __truediv__(self, other): return Point(self.x / other, self.y / other)
    def __hash__(self): return hash((self.x, self.y))
    def __eq__(self, other): return (self.x, self.y) == (other.x, other.y)
    def __repr__(self): return '({}, {})'.format(self.x, self.y)

# three distinct points define a circle
#   a, b, c
#
#   <a-p,a-p> - r^2 = 0 (1)
#   <b-p,b-p> - r^2 = 0 (2)
#   <c-p,c-p> - r^2 = 0 (3)
#
#   Taking (2) - (1) eliminates terms leading to:
#       <b,b> - <a,a> - 2<p,b-a> = 0
#   Taking (3) - (1) eliminates terms leading to:
#       <c,c> - <a,a> - 2<p,c-a> = 0
#   
#   Solving each of these for p.x and setting them equal to each other gives
#       <b,b> - <a,a> - 2p.y(b.y-a.y)   <c,c> - <a,a> - 2p.y(c.y-a.y)
#       ----------------------------- = -----------------------------
#             2(b.x-a.x)                      2(c.x-a.x)
#
#   Let B = <b,b> - <a,a>               C = <c,c> - <a,a>
#       D = 2(b.y-a.y)                  E = 2(c.y-a.y)
#       F = 2(b.x-a.x)                  G = 2(c.x-a.x)
#   
#   Gives (B - p.y * D) / F = (C - p.y * E) / G
#
#   and p.y = (F*C - G*B) / (F*E - G*D)
#
#   Then plug in p.y to get p.x, and then both to get r^2


def min_diameter_circle(points):
    # points must be unique

    # find a bound on the minimum radius needed to exclude some options
    required_r2 = 0
    for i, a in enumerate(points):
        for b in points[i+1:]:
            p = (a + b) / 2
            ap = p - a
            required_r2 = max(required_r2, ap.dot(ap))

    min_r2 = 1e100
    # smallest circle defined by two points
    for i, a in enumerate(points):
        for b in points[i+1:]:
            p = (a + b) / 2
            r2 = (a - p).dot(a - p)
            if required_r2 <= r2:
                for d in points:
                    dp = p - d
                    if r2 < dp.dot(dp):
                        break
                else:
                    min_r2 = min(min_r2, r2)

    # smallest circle defined by three points
    for i, a in enumerate(points):
        a_dot_a = a.dot(a)
        for j, b in enumerate(points[i+1:]):
            b_dot_b = b.dot(b)

            B = b_dot_b - a_dot_a
            D = 2 * (b.y - a.y)
            F = 2 * (b.x - a.x)

            for c in points[j+1:]:

                C = c.dot(c) - a_dot_a
                E = 2 * (c.y - a.y)
                G = 2 * (c.x - a.x)

                denom = F * E - G * D
                if denom == 0:
                    # a, b, c are collinear
                    continue
                num = F * C - G * B

                # now we have the center
                py = num / denom
                #px = (-A - py * C) / B if B else (-D - py * F) / E
                px = (B - py * D) / F if F else (C - py * E) / G
                p = Point(px, py)
                # and the radius^2
                ap = p - a
                r2 = ap.dot(ap)

                # sanity check that the center is equidistant from the three points
                #assert abs(1 - (p - a).dot(p - a) / (p - b).dot(p - b)) < 1e-3, (a, b, p, (p - a), (p - b))
                #assert abs(1 - (p - a).dot(p - a) / (p - c).dot(p - c)) < 1e-3, (a, c, p, (p - a), (p - c))

                if min_r2 <= r2:
                    # don't bother checking, we already have a smaller radius^2
                    continue

                if r2 < required_r2:
                    # cannot capture all the points
                    continue

                for d in points:
                    dp = p - d
                    if r2 < dp.dot(dp):
                        break
                else:
                    min_r2 = min(min_r2, r2)

    return math.sqrt(min_r2) * 2

def main():
    n = int(sys.stdin.readline())
    points = [tuple(map(fractions.Fraction, sys.stdin.readline().split())) for _ in range(n)]

    xy = list({Point(x, y) for x, y, z in points})
    xz = list({Point(x, z) for x, y, z in points})
    yz = list({Point(y, z) for x, y, z in points})

    smallest = 1e100
    for pts in [xy, xz, yz]:
        smallest = min(smallest, min_diameter_circle(pts))

    print('{:0.10f}'.format(smallest))

if __name__ == '__main__':
    main()

