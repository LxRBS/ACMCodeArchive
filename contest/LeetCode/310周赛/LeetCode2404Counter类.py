"""
�������飬�ҳ��ִ�����������ֵ��С��ż��
�ֵ䣬Ҳ����ֱ��ʹ��Counter��
"""

class Solution(object):
    def mostFrequentEven(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        cnt = collections.Counter(nums)
        tmpk, tmpv = 10**6, 0
        for k, v in cnt.items():
            if k % 2 == 1: continue
            if v > tmpv or (v == tmpv and k < tmpk):
                tmpk, tmpv = k, v
        return tmpk if tmpk != 10**6 else -1