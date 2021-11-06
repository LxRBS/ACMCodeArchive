#!/usr/bin/env python3

import sys
import math

n = int(sys.stdin.readline())
numbers = list(map(int, sys.stdin.readline().split()))

# precompute the runs of "1"s in the numbers, which we know does not change the
# product
numbers.append(0) # in case the numbers ends in "1"
end_ones = [-1] * n
for i in range(1, n+1):
    if numbers[i-1] == 1 and numbers[i] != 1:
        # we have found the end of a run; record the end point at each point
        # during the run
        j = i - 1
        while j and numbers[j] == 1:
            end_ones[j] = i
            j -= 1
numbers.pop()

# if the product gets larger than this, it never gets smaller, so we can break
# out of the current inner loop
LARGEST_SUM = (10 ** 5) * (10 ** 9)

ans = 0
for i, x in enumerate(numbers):
    s = p = x
    j = i + 1
    while j < n:
        y = numbers[j]

        # treat each run of "1"s specially, skipping ahead to the end
        if y == 1:
            endsum = s + end_ones[j] - j
            # Is there a match somewhere in this range? If so, there can be at
            # most one.
            if s + 1 <= p <= endsum:
                ans += 1
            # skip ahead to the end of the run of 1s
            j = end_ones[j]
            s = endsum
        else:
            # the normal case
            s += y
            p *= y
            if (LARGEST_SUM < p) or (p - s > n - j - 1):
                break
            if s == p:
                ans += 1
            j += 1

print(ans)
