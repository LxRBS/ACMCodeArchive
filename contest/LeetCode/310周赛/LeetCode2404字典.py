"""
�������飬�ҳ��ִ�����������ֵ��С��ż��
�ֵ�
"""

class Solution(object):
    def mostFrequentEven(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        cnt = {}  # �ֵ�
        for ai in nums:
            if ai % 2 == 0:
                if ai in cnt: cnt[ai] += 1
                else: cnt[ai] = 1
        tmpk, tmpv = 10**6, 0
        for k, v in cnt.items():
            if v > tmpv or (v == tmpv and k < tmpk):
                tmpk, tmpv = k, v
        return tmpk if tmpk != 10**6 else -1