#!/usr/bin/env python3

# written to ensure that the presentation slide strategy is actually correct

import sys

if __name__ == '__main__':
    m = int(sys.stdin.readline())
    weights = [int(sys.stdin.readline()) for _ in range(m)]
    unique_weights = sorted(set(weights))
    multiplicity = {}
    for w in weights:
        multiplicity[w] = multiplicity.get(w, 0) + 1

    P = []
    for w in unique_weights:
        P.append((P[-1] if P else 0) + w * multiplicity[w])

    answer = None
    for i, w in enumerate(unique_weights):
        if P[i] == P[-1] + w * multiplicity[w] - P[i]:
            answer = w
        elif P[i] == P[-1] - P[i]:
            answer = w + 1

    assert answer is not None
    print(answer)

