"""
给定数组，找出现次数最多的且数值最小的偶数
字典，也可以直接使用Counter类
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