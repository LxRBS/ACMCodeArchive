# encoding: utf-8
'''
主角有hc的血dc的攻击，怪物有hm的血dm的攻击，
主角有k个硬币，每个硬币可以加w的攻击或者a的血
主角可以任意选择。问加成之后，主角是否能赢
本质上就是问： hc/dm向上取整 >= hm/dc向上取整
是否成立
设x个加在血上，y个加在攻击上，则
(hc+xa)/dm - hm/(dc+yw) = ((hc+xa)*(hc+yw)-hm*dm) / 分母
分母显然大于0，只需分子大于0即可，分子是一个二次函数，开口向下，可以求对称轴
但由于有向上取整的存在，因此不完全恰好在对称轴旁。往两边延伸都取一些数尝试即可
由于所有参数都很大，因此使用python
标程解法：因为k只有1E5，因此枚举。
'''
import sys
sys.setrecursionlimit(10**6) 

def isOK(hc, dc, hm, dm, k, w, a, x): 
    if x < 0 or x > k: return False
    ndc = dc + x * w
    nhc = (k - x) * a + hc
    t = hm // ndc
    if hm % ndc != 0: t += 1
    t -= 1
    return nhc > t * dm

def f(hc, dc, hm, dm, k, w, a):
    if 0 == a: 
        dc += k * w
        return hc // dm + (1 if hc % dm != 0 else 0) >= hm // dc + (1 if hm % dc != 0 else 0)
    if 0 == w:
        hc += k * a
        return hc // dm + (1 if hc % dm != 0 else 0) >= hm // dc + (1 if hm % dc != 0 else 0)
    x = (hc*w+a*k*w-a*dc+w*w) // (2*a*w)
    if isOK(hc, dc, hm, dm, k, w, a, x): return True
    for i in range(1, 150):
        if isOK(hc, dc, hm, dm, k, w, a, x+i): return True
        if isOK(hc, dc, hm, dm, k, w, a, x-i): return True 
    if isOK(hc, dc, hm, dm, k, w, a, 0): return True
    if isOK(hc, dc, hm, dm, k, w, a, k): return True
    return False
 
if __name__ == '__main__':
    # sys.stdin = open('1.txt',   'r')
    nofkase = int(input())
    for kase in range(nofkase):
        hc, dc = [int(i) for i in input().split()]
        hm, dm = [int(i) for i in input().split()]
        k, w, a = [int(i) for i in input().split()]
        print('YES' if f(hc, dc, hm, dm, k, w, a) else 'NO')


