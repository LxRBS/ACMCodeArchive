"""
���ַ������ֳ������Ӵ�����ÿ���Ӵ��е���ĸ����Ψһ��
��Ȼ��̰�ķ�����s0��ʼ�����Ĺ���һ���Ӵ���������ظ�����ĸ���ؿ�һ���µ��Ӵ�
��set��¼��ĸ�Ƿ���ֹ�
"""

class Solution(object):
    def partitionString(self, s):
        """
        :type s: str
        :rtype: int
        """
        if 0 == len(s): return 0

        ans, flag = 1, set()
        flag.add(s[0])
        for si in s[1::]:
            if si in flag:
                flag.clear()
                flag.add(si)
                ans += 1
            else:
                flag.add(si)
        return ans