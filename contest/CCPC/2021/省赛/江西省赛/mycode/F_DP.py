# encoding: utf-8
import sys
sys.setrecursionlimit(10**6)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    a = [0]
    p2 = [1, 2]
    k = 1
    while len(a) <= 10000:
        for i in range(k+1):
            a.append(k)
        k += 1
        p2.append(p2[-1]*2)
    # print(a)
    # print(p2)
    ans = [0, 1]
    for i in range(2, 10001):
        ans.append(ans[-1] + p2[a[i-1]])
    # print(ans)
    nofkase = int(input())
    for kase in range(nofkase):
        n = int(input())
        print(ans[n])
        