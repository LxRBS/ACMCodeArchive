s = int(input())
i = 0
while i * i <= s:
    j = 0
    while i * i + j * j < s:
        j += 1
    if i * i + j * j == s:
        print(0, 0)
        print(i, j)
        print(-j, i)
        print(i - j, j + i)
        exit()
    i += 1

print("Impossible")