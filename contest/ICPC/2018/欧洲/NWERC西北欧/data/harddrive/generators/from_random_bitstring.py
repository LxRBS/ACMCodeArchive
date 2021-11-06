#!/usr/bin/python3
import time
import random

N_max = 10**6

seed = random.seed(time.time())   # seed for random bitstring, change for deterministic values.

prob_zerobit = 0.5   # probability that a bit is zero
prob_broken = 0.1    # probability that a zerobit is broken (and so leaked)

def get_random_input():
    # return ((n, e, b), [bis]) like specified by input
    n = random.randint(2, N_max)
    e = 0
    bis = set()

    bitstring = ['0' if random.random() < prob_zerobit else '1' for _ in range(n-1)]
    bitstring.append('0')
    for i in range(len(bitstring)-1):
        e += 0 if bitstring[i+1] == bitstring[i] else 1
        if bitstring[i] == '0' and random.random() < prob_broken:
            bis.add(i+1)

    bis.add(n)
    bis.discard(1)

    return ((n, e, len(bis)), list(bis))

def print_input(inp):
    print("{} {} {}".format(*inp[0]))
    print(" ".join(map(str, sorted(inp[1]))))

if __name__ == '__main__':
    print_input(get_random_input())
