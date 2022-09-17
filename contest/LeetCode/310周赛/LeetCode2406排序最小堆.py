"""
�������ɸ����䣬���ܹ�����Щ���仮�ֳɶ��ٸ����֣�ʹ��ÿ������������以���ص�
����һ�����ƣ�Ҳ��̰�ģ������Ĺ�Ϊһ�࣬ʵ�ڲ����˲ŷֿ�
������������������Ȼ������������Ҫ����
�Ȱ���ʼʱ���ٰ�����ʱ�䡣��ÿһ����ǰ����[si, ei]�����si��֮ǰ��С�Ľ���ʱ�仹ҪС��
��ǰ����ֻ���·�һ�������򣬾ͽ���ǰ��������С�Ľ���ʱ��ֵ�һ����
��ȡ��С����ʱ�����ʹ����С��
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