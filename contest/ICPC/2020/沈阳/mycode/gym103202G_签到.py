n, k = [int(i) for i in input().split()]
a = [int(i) for i in input().split()]
a.sort()
print(sum(a[n-k::]))