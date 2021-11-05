# encoding: utf-8
# 7的倍数或者含有7的数字
# 数位DP

D = [[[-1 for j in range(7)], [-1 for j in range(7)]] for i in range(13)]
Dig = []


def dfs(pos, status, remainder, limit):
    """
    pos: 数位，从高到0
    status: 是否含7,1或者0
    remainder: 对7的余数
    limit: 是否受限
    """
    global D
    if -1 == pos:
        return 1 if (1 == status or 0 == remainder) else 0
    if limit is False and -1 != D[pos][status][remainder]:
        return D[pos][status][remainder]
    last = Dig[pos] if limit else 9
    ans = 0
    for i in range(last+1):
        ans += dfs(pos-1, 1 if i == 7 or 1 == status else 0, (remainder*10+i) % 7, limit and i == last)
    if limit is False:
        D[pos][status][remainder] = ans
    return ans


def ddp(n):
    global Dig
    Dig = []
    while n != 0:
        Dig.append(n%10)
        n = n // 10
    return dfs(len(Dig)-1, 0, 0, True)


if __name__ == '__main__':
    n, m = [int(i) for i in input().split()]
    lower = ddp(n)
    target = lower + m
    left = n
    right = 10000000000000
    while True:
        mid = (left + right) // 2
        if ddp(mid) < target:
            left = mid + 1
        else:
            right = mid - 1
        if left > right:
            break
    print(left)