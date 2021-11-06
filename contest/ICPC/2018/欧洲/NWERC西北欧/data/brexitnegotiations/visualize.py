#!/usr/bin/env python

def readLine():
    return map(int, raw_input().split())

print("digraph g {")
n = readLine()[0]
for i in range(n):
    nums = readLine()
    mins = nums.pop(0)
    edges = nums.pop(0)
    print("node" + str(i+1) + "[label=\"" + str(i+1) + "\n" + str(mins) + "mins\"]")
    for n in nums:
        print("node" + str(n) + " -> node" + str(i+1) + ";")

print("}")
