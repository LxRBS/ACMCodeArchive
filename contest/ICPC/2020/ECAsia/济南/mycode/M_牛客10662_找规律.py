# encoding: utf-8
"""
锅的容量是K，煎饼的数量是N，每个饼要煎两面，每面花费一个小时
问最少要几个小时
整倍数的直接×2即可
然后看余数是否超过了K/2，如果超过了还是要加2，否则加1即可
"""
import sys
def f(n, k):
    if n <= k: return 2
    tmp = n // k
    r = n % k
    if 0 == r: return tmp + tmp
    return tmp + tmp + (1 if r <= k // 2 else 2)   
    
    
n, k = [int(i) for i in input().split()]
print(f(n, k))
