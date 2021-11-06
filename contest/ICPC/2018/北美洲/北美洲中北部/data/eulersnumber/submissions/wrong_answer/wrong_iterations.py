#!/usr/bin/env python3

def euler(n):
    val = 0
    fact = 1

    # wrong number of iterations (should be n+1)
    for i in range(n):
        if i != 0:
            fact *= i
        val += 1/fact
    return val

n = int(input())
print(euler(n))
