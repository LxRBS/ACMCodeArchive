import os

print("Input number of tests:")
n = int(input())
for i in range(n):
    print("copy %02d %02d.in" % (i + 1, i + 1))
    os.system("copy %02d %02d.in" % (i + 1, i + 1))