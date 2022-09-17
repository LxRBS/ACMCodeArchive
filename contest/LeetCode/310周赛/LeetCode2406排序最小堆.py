"""
给定若干个区间，问能够把这些区间划分成多少个部分，使得每个部分里的区间互不重叠
与上一题类似，也是贪心，尽量的归为一类，实在不行了才分开
但是输入与结果并不天然有序，所以首先要排序。
先按开始时间再按结束时间。对每一个当前区间[si, ei]，如果si比之前最小的结束时间还要小，
则当前区间只能新分一拨。否则，就将当前区间与最小的结束时间分到一拨。
获取最小结束时间可以使用最小堆
"""

class Solution(object):
    def minGroups(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        if 0 == len(intervals): return 0
        intervals.sort()
        q = []
        for li in intervals:
            if 0 == len(q): heapq.heappush(q, li[1])
            else:
                a = heapq.heappop(q)
                if a < li[0]: heapq.heappush(q, li[1])
                else: heapq.heappush(q, a); heapq.heappush(q, li[1])
        return len(q)