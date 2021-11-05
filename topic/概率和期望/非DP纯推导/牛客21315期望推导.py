# encoding: utf-8
"""
    N�����У�M����壬һ��ʼû���κε�·
    �����ѡһ����壬ѡ����������ĳ��л��������ӵ���壬�޽�һ����·
    �ʵ�·���������Ƕ��٣�������������ӵ����л��߼�����ӵ�����
    E = SIGMA{1/n!*SIGMA{Di}}��
    ����Di��ʾ��ǰ��������е�i������������ĳ��л���ǰ����������ľ���
    ���Կ���ÿһ��vi��E�Ĺ��ף���ciΪvi����ĳ��У�����x������ci����
    ����x=0�����κ�����¶���D(vi,ci)
    ����x=1����vj1����vi֮ǰʱΪD(vi,vj1)������ΪD(vi,ci)
    ����ȫ���У�vj1��vi֮ǰ�ĸ��ʣ�Ϊ1/2���õ�ci�ĸ���Ϊ1/2
    ����x=2��˳��������[vj1,vj2]����vj1��֮ǰ��D(vi,vj1)��������1/2
    ��vj2��֮ǰ��vj1��֮����D(vi,vj2)����ʱ������(1/2)*(1/3)
    �õ�ci�ĸ�����1/3
    ����x=3��˳��������[vj1,vj2,vj3]�����õ�vj1�ĸ�����1/2
    �õ�vj2�ĸ�����(1/2)*(1/3)���õ�vj3�ĸ�����1/4!*2=(1/3)*(1/4)
    �õ�ci�ĸ�����1/4
    ����x=4���õ�vj4�ĸ�����1/5!*3!=(1/4)*(1/5)���õ�ci�ĸ�����1-1/5
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
    # ��������ĳ���
    nearest_city = [1E100 for i in range(m)]
    for i in range(m):
        for j in range(n):
            nearest_city[i] = min(nearest_city[i], dist(villagex[i], villagey[i], cityx[j], cityy[j]))
    # �������������໥����
    d = [[0.0 for j in range(m)] for i in range(m)]
    for i in range(m):
        for j in range(i+1, m):
            d[i][j] = d[j][i] = dist(villagex[i], villagey[i], villagex[j], villagey[j])
    # ����
    ans = 0.0
    for i in range(m):  # forÿһ�����
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