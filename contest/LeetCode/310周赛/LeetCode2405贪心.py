"""
将字符串划分成若干子串，且每个子串中的字母都是唯一的
显然用贪心法，从s0开始尽量的归在一个子串里，碰到了重复的字母才重开一个新的子串
用set记录字母是否出现过
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