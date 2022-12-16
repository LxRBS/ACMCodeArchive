# 给定UDLR的行走顺序，问行走过程中距离原点最远的距离是多少
# 循环模拟一遍即可

import math

D = {'U': (0, 1), 'D': (0, -1), 'L': (-1, 0), 'R': (1, 0)}

def dist(a, b):
    x = a[0] - b[0]
    y = a[1] - b[1]
    return x * x + y * y

def proc():
    n = int(input())
    a = input()
    ans = 0
    origin = (0, 0)
    cur = [0, 0]
    for ai in a:
        cur[0] += D[ai][0]
        cur[1] += D[ai][1]
        ans = max(ans, dist(origin, cur))
    return math.sqrt(ans)


if __name__ == '__main__':
    nofkase = int(input())
    for kase in range(nofkase):
        print('%.12f' % proc())