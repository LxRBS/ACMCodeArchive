n, m, k = [int(i) for i in input().split()]
if n > k: print("YES")
elif m > k: print("YES")
elif n + m > k: print("YES")
else: print("NO")