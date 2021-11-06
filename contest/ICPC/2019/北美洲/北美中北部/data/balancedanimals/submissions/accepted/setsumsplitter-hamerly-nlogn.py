#!/usr/bin/env python3

import sys

if __name__ == '__main__':
    m = int(sys.stdin.readline())
    weights = [int(sys.stdin.readline()) for _ in range(m)]

    multiplicity = {}
    for w in weights:
        multiplicity[w] = multiplicity.get(w, 0) + 1

    weights.sort()
    unique_weights = sorted(set(weights))

    _sum = sum(weights)
    left_sum = 0
    answer = None

    for i, w in enumerate(unique_weights):
        if left_sum == _sum - left_sum - w * multiplicity[w]:
            answer = w
        elif i + 1 < len(unique_weights) and (w + 1) != unique_weights[i+1]:
            ls = left_sum + w * multiplicity[w]
            if ls == _sum - ls:
                answer = w + 1

        left_sum += w * multiplicity[w]

    assert answer is not None
    print(answer)

