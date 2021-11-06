N = int(input())
A, B = map(int, input().split())

best_k = 2000
for i in range(0, N+1):
    for j in range(0, N+1):
        if (i * A + j * B) % N != 0: continue
        if i + j == 0: continue
        best_k = min(best_k, i+j)
print(best_k)        