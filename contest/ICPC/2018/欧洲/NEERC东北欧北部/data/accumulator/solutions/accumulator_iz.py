t, p = map(int, input().split())
p -= max(0, 20 - p)
print(str((p + 20.0) * t / (100 - p)))