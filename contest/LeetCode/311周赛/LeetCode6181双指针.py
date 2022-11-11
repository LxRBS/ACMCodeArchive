"""
����abc����xyz֮��Ĵ���Ϊ�Ǻϸ��
����s������ĺϸ��Ӵ��ĳ���
˫ָ��O(N)��һ��
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