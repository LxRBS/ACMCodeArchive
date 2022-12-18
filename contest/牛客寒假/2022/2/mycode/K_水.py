s = [int(i) for i in input()]
a = [0 for i in range(10)]

for i in s:
    if i == 5: continue
    a[i] += 1
    a[5] += 1
for ai in a[1::]:
    print(ai, end=' ')