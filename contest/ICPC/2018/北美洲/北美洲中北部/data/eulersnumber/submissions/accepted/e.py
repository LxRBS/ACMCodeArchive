#!/usr/bin/env python3

def euler(n):
    # mistake file here for range(n) not n+1
    val = 0
    # mistake: make sure someone isn't calling factorial each time
    fact = 1
    for i in range(n+1):
        if i != 0:
            fact *= i
        val += 1/fact
    return val

n = int(input())
print(euler(n))
