raw_input()
v = min(x/(i+1) if x <= i+1 else -1 for (i, x) in enumerate(sorted(map(float, raw_input().split()))))
print v if v >= 0 else 'impossible'
