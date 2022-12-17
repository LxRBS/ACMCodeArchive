"""
初始有X体力，杀球消耗体力a，不杀则回复体力b
只有当字符是1才有可能杀球。给定字符串s，问最多能杀多少次球
显然贪心，能杀就杀
"""

def proc(x, a, b, s):
    ans = 0
    for si in s:
        if '1' == si:
            if x >= a:
                ans += 1
                x -= a
            else:
                x += b
        else:
            x += b
    return ans

if __name__ == '__main__':
    x, a, b = [int(i) for i in input().split()]
    s = input()
    print(proc(x, a, b, s))