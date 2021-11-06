#!/usr/bin/env pypy
import glob
import os
import random
import re
import textwrap

'''
Let's kill some terrible sort implementations.
'''
def main():
  remove_existing_cases()

  write_case(1, 'small_reverse_sorted', lambda: range(100,0,-1),
      '''
      Sanity check to make sure teams are actually sorting the list.
      ''')
  write_case(2, 'big_already_sorted', lambda: range(1,2*10**5+1),
      '''
      Worst case for quicksort implementations which naively use the
      first or last element as the pivot every time.
      ''')
  write_case(3, 'big_ones', lambda: [1 for i in range(1,2*10**5+1)],
      '''
      Worst case for quicksort implementations which do not filter
      out the pivot before subdividing. May also catch some broken
      bucket or radix sorts if they reallocate the bucket for each
      new entry.
      ''')
  # write_case(4, 'middle-sorted', anti_quicksort_mid(10**5))

'''
Cleanup from previous runs.
'''
def remove_existing_cases():
  assert os.path.isdir('secret'), \
      'secret/ dir does not exist. Are you running from inside data/?'

  for f in glob.glob('secret/*-gen-*.*'):
    os.remove(f)

'''
Mini input validator.
'''
def check_constraints(data):
  assert 0 <= min(data) and max(data) <= len(data)
  assert 1 <= len(data) <= 2*10**5

'''
Copied from rgl.py
'''
def solve_case(data):
  res = [b/a for a,b in zip(range(1,len(data)+1), sorted(data))]
  return 'impossible' if max(res) > 1 else '%.10f' % (min(res))

'''
Given a case number-name and raw data:
  - seed with a salted value
  - run generator
  - format output and write to casename.in
  - generate a solution'using solve_case and write to casename.ans
'''
def write_case(num, name, generator, desc=None):
  random.seed(name + '-salt=nwerc2018')
  data = list(generator())

  name = '%02d-gen-%s' % (num, name)

  with open('secret/' + name + '.in', 'w') as fin:
    fin.write('%d\n' % (len(data)))
    fin.write(' '.join(map(str, data)) + "\n")

  with open('secret/' + name + '.ans', 'w') as fans:
    fans.write('%s\n' % solve_case(data))

  if desc:
    with open('secret/' + name + '.desc', 'w') as fdesc:
      desc = '\n'.join(textwrap.wrap(re.sub('\s+', ' ', desc.strip()), 80))
      fdesc.write('%s\n' % (desc))

if __name__ == '__main__':
  main()
