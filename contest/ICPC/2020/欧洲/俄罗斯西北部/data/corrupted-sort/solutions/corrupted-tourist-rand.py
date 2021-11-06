import sys
import random
n = int(input())
random.seed(0)
while True:
  i = random.randint(1, n - 1)
  print(i, i + 1)
  sys.stdout.flush()
  s = input()
  if s == 'WIN':
    exit()
