# encoding: utf-8
"""
    N个城市，M个乡村，一开始没有任何道路
    随机挑选一个乡村，选择与其最近的城市或者已连接的乡村，修建一条道路
    问道路期望长度是多少，将所有乡村连接到城市或者间接连接到城市
    E = SIGMA{1/n!*SIGMA{Di}}，
    其中Di表示当前乡村排列中第i个村子与最近的城市或者前面最近的乡村的距离
    可以考虑每一个vi对E的贡献，令ci为vi最近的城市，且有x个乡村比ci更近
    假设x=0，则任何情况下都是D(vi,ci)
    假设x=1，则当vj1排在vi之前时为D(vi,vj1)，否则为D(vi,ci)
    考虑全排列，vj1在vi之前的概率，为1/2，用到ci的概率为1/2
    假设x=2，顺序依次是[vj1,vj2]，则当vj1在之前，D(vi,vj1)，概率是1/2
    当vj2在之前且vj1在之后是D(vi,vj2)，此时概率是(1/2)*(1/3)
    用到ci的概率是1/3
    假设x=3，顺序依次是[vj1,vj2,vj3]，则用到vj1的概率是1/2
    用到vj2的概率是(1/2)*(1/3)，用到vj3的概率是1/4!*2=(1/3)*(1/4)
    用到ci的概率是1/4
    假设x=4，用到vj4的概率是1/5!*3!=(1/4)*(1/5)，用到ci的概率是1-1/5
    ...
"""
from math import sqrt
import sys
sys.setrecursionlimit(10**6)


def dist(x1, y1, x2, y2):
    x, y = x1 - x2, y1 - y2
    return sqrt(x * x + y * y)


if __name__ == '__main__':
    # sys.stdin = open('1.txt', 'r')
    n, m = [int(i) for i in input().split()]
    cityx = [float(i) for i in input().split()]
    cityy = [float(i) for i in input().split()]
    villagex = [float(i) for i in input().split()]
    villagey = [float(i) for i in input().split()]
    # 计算最近的城市
    nearest_city = [1E100 for i in range(m)]
    for i in range(m):
        for j in range(n):
            nearest_city[i] = min(nearest_city[i], dist(villagex[i], villagey[i], cityx[j], cityy[j]))
    # 计算所有乡村的相互距离
    d = [[0.0 for j in range(m)] for i in range(m)]
    for i in range(m):
        for j in range(i+1, m):
            d[i][j] = d[j][i] = dist(villagex[i], villagey[i], villagex[j], villagey[j])
    # 计算
    ans = 0.0
    for i in range(m):  # for每一个乡村
        a = []
        for j in range(m):
            if i == j: continue
            if d[i][j] < nearest_city[i]:
                a.append(d[i][j])
        a.sort()
        for j, ai in enumerate(a):
            ans += ai / (j + 1) / (j + 2)
        ans += nearest_city[i] * 1.0/(len(a)+1)
    print(ans)