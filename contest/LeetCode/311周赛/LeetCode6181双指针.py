"""
类似abc或者xyz之类的串认为是合格的
给定s，问最长的合格子串的长度
双指针O(N)跑一遍
"""
class Solution(object):
    def longestContinuousSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        k, n, ans = 0, len(s), 1
        while True:
            t = k + 1
            while t < n and ord(s[t]) == ord(s[t-1]) + 1:
                t += 1
            ans = max(ans, t - k)
            k = t
            if k == n: break
        return ans