import sys
n = int(input())
while True:
  for i in list(range(1, n)) + list(range(n - 1, 0, -1)):
    print(i, i + 1)
    sys.stdout.flush()
