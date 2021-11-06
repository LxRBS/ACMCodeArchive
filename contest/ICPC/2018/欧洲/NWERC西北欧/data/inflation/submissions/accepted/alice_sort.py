n = input()
gas = sorted(map(int, raw_input().split()))
mi = 1.1
for b, h in enumerate(gas, start=1):
    if h > b:
        print("impossible")
        exit(0)
    mi = min(float(h) / b, mi)
print(mi)
