def proc(n, a):
    s = 1
    for ai in a:
        s = s * ai
    return 2022 * (s + n - 1)


nofkase = int(input())
for kase in range(nofkase):
    n = int(input())
    a = [int(i) for i in input().split()]
    print(proc(n, a))