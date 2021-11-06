import sys
n = int(input())
cnt = 0
while cnt < 10000:
  for i in list(range(1, n)) + list(range(n - 1, 0, -1)):
    print(i, i + 1)
    sys.stdout.flush()
    cnt += 1
    if cnt >= 10000:
      break
