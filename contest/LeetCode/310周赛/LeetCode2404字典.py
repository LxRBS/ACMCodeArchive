"""
给定数组，找出现次数最多的且数值最小的偶数
字典
"""

class Solution(object):
    def mostFrequentEven(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        cnt = {}  # 字典
        for ai in nums:
            if ai % 2 == 0:
                if ai in cnt: cnt[ai] += 1
                else: cnt[ai] = 1
        tmpk, tmpv = 10**6, 0
        for k, v in cnt.items():
            if v > tmpv or (v == tmpv and k < tmpk):
                tmpk, tmpv = k, v
        return tmpk if tmpk != 10**6 else -1