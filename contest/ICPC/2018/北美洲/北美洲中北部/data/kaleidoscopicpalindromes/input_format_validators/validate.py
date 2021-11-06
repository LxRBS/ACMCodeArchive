#!/usr/bin/python3

import re
import sys

integer = "(0|[1-9]\d*)"
threeint = re.compile(integer + " " + integer + " " + integer + "\n")

line = sys.stdin.readline()
assert threeint.match(line)
a, b, edges = eval("(" + line.replace(" ", ',') + ")")

line = sys.stdin.readline()

# Error to have more data
if line:
    sys.exit(1)

sys.exit(42)
