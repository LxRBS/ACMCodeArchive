"""
�������ΪstartPos���յ�ΪendPos������k��ǡ�ô���㵽�յ�ķ��������Ƕ���
����Ҫ��endPos-startPos����Ȼ��ʣ�µĲ�����Ȼ������ż������һ�볯��һ�볯��
��left = k - (endPos-startPos)
���ǿ�֪��������һ��Ҫ��a=k-left/2�����򸺷���һ��Ҫ��b=left/2����ֻҪ�����������
��һ�����ߵ����������������߸���ʵ����ν�����Ա����Ͼ�����a��+1��b��-1��ͬ�����������Ƕ���
��ת��Ϊ��ʵ�����ʴ�a+b��λ��ѡ��b��λ�����ó�-1�ķ������Ƕ��٣����������C(a+b, b)
�������������������μ���(1000*1000����)��ֱ����__init__���������
����������ģ���Ϊÿ�ζ�������10**6�������
"""

class Solution(object):
    mod = 1000000007 # ģ��
    c = [[1 for i in range(1001)] for j in range(1001)]
    def __init__(self): # ������Ǽ��������
        for i in range(1, 1001):
            for j in range(1, i):
                self.c[i][j] = (self.c[i-1][j] + self.c[i-1][j-1]) % self.mod

    def numberOfWays(self, startPos, endPos, k):
        """
        :type startPos: int
        :type endPos: int
        :type k: int
        :rtype: int
        """
        left = k - (endPos - startPos)
        if left < 0 or left % 2 == 1: return 0
        return self.c[k][left//2]