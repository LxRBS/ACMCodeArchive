#!/usr/bin/env python3

import sys

# incorrectly assumes that the answer will be near the mean

if __name__ == '__main__':
    m = int(sys.stdin.readline())

    weights = [int(sys.stdin.readline()) for _ in range(m)]

    mean = sum(weights) / len(weights)
    mean_floor = int(mean)

    target = -10000
    for w in weights:
        if target < w <= mean_floor:
            target = w

    for t in range(target - 1, target + 4):
        less = sum([w for w in weights if w < t])
        greater = sum([w for w in weights if w > t])
        if less == greater:
            print(t)
            break
    else:
        print(max(weights)) # give up

