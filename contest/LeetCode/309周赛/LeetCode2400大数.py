"""
�������ΪstartPos���յ�ΪendPos������k��ǡ�ô���㵽�յ�ķ��������Ƕ���
����Ҫ��endPos-startPos����Ȼ��ʣ�µĲ�����Ȼ������ż������һ�볯��һ�볯��
��left = k - (endPos-startPos)
���ǿ�֪��������һ��Ҫ��a=k-left/2�����򸺷���һ��Ҫ��b=left/2����ֻҪ�����������
��һ�����ߵ����������������߸���ʵ����ν�����Ա����Ͼ�����a��+1��b��-1��ͬ�����������Ƕ���
��ת��Ϊ��ʵ�����ʴ�a+b��λ��ѡ��b��λ�����ó�-1�ķ������Ƕ��٣����������C(a+b, b)
�������������������μ���(1000*1000����)
Ҳ����ֱ�Ӽ��㣬python֧�ִ��������Կ�����������ȡģ�������������ܻ�Ƚ������ÿ�����Ч��
�������LeetCode���ǿ��Թ���
"""

class Solution(object):
    def numberOfWays(self, startPos, endPos, k):
        """
        :type startPos: int
        :type endPos: int
        :type k: int
        :rtype: int
        """
        left = k - (endPos - startPos)
        if left < 0 or left % 2 == 1: return 0
        return self.C(k, left//2) % 1000000007

    def C(self, a, b): # ����C(a, b)
        return self.fac(a) // self.fac(b) // self.fac(a - b)
    def fac(self, n):
        ans = 1
        for i in range(1, n+1): ans *= i
        return ans