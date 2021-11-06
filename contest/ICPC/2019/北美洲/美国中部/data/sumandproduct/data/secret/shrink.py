#!/usr/bin/python

# use this to shrink the data down to a smaller max-n
# run as: python shrink.py *.in

import re
import sys
import subprocess

MAXN = 100000

for filename in sys.argv[1:]:
    print(filename)
    with open(filename) as f:
        f.readline()
        nums = list(map(int, f.readline().split()))
        nums = nums[:MAXN]
    
    with open(filename, 'w') as out:
        out.write('{}\n'.format(len(nums)))
        out.write(' '.join(map(str, nums)) + '\n')

    ans_filename = re.sub('.in$', '.ans', filename)

    subprocess.call('pypy ../../submissions/accepted/bowen.py < {} > {}'.format(filename, ans_filename), shell=True)
