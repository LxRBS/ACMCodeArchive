"""
�������ΪstartPos���յ�ΪendPos������k��ǡ�ô���㵽�յ�ķ��������Ƕ���
����Ҫ��endPos-startPos����Ȼ��ʣ�µĲ�����Ȼ������ż������һ�볯��һ�볯��
��left = k - (endPos-startPos)
���ǿ�֪��������һ��Ҫ��a=k-left/2�����򸺷���һ��Ҫ��b=left/2����ֻҪ�����������
��һ�����ߵ����������������߸���ʵ����ν�����Ա����Ͼ�����a��+1��b��-1��ͬ�����������Ƕ���
��ת��Ϊ��ʵ�����ʴ�a+b��λ��ѡ��b��λ�����ó�-1�ķ������Ƕ��٣����������C(a+b, b)
�������������������μ���(1000*1000����)
��Ԫ�������������û��ֱ��ʹ�ô����飬���������ݲ�����
"""

class Solution(object):
    mod = 1000000007 # ģ��
    def numberOfWays(self, startPos, endPos, k):
        """
        :type startPos: int
        :type endPos: int
        :type k: int
        :rtype: int
        """
        left = k - (endPos - startPos)
        if left < 0 or left % 2 == 1: return 0
        return self.C(k, left//2)

    def pow(self, a, n): # �����ݼ���a^n%mod
        ans = 1
        while n != 0:
            if n & 1: ans = ans * a % self.mod
            a = a * a % self.mod
            n >>= 1
        return ans
    def inv(self, a): # ����a���棬�� a^(-1)*a%mod==1
        return self.pow(a, self.mod-2)
    def fac(self, n): # ����׳�ȡģ
        ans = 1
        for i in range(1, n+1): ans = ans * i % self.mod
        return ans
    def C(self, n, m): # ���������
        return self.fac(n) * self.inv(self.fac(m)) % self.mod * self.inv(self.fac(n-m)) % self.mod