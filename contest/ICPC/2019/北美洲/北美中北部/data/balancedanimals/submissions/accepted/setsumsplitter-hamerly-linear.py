#!/usr/bin/env python3

# this approach uses no comparison-based sorting

import sys

if __name__ == '__main__':
    m = int(sys.stdin.readline())
    weights = [int(sys.stdin.readline()) for _ in range(m)]

    # this is a bucket sort, so it's not really *no* sorting...
    grouped_weights = [0] * (max(weights) + 2)
    for w in weights:
        grouped_weights[w] += w

    unique_weights = []
    for w in range(len(grouped_weights)):
        if grouped_weights[w]:
            unique_weights.append(w)

    total_weight = sum(weights)
    left_sum = 0
    for w in unique_weights:
        if left_sum + grouped_weights[w] == total_weight - left_sum:
            print(w)
            break
        elif grouped_weights[w+1] == 0 and left_sum + grouped_weights[w] == total_weight - left_sum - grouped_weights[w]:
            print(w + 1)
            break
        left_sum += grouped_weights[w]
    else:
        assert False

