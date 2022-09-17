
"""
�����ַ���s��һ��distance���飬��
distance[ai]�Ƿ�ǡ����s����ĸai�ľ���
"""

class Solution(object):
    def checkDistances(self, s, distance):
        """
        :type s: str
        :type distance: List[int]
        :rtype: bool
        """
        pos = [-1 for i in range(26)]
        for i, si in zip(range(len(s)), s):
            ch = ord(si) - ord('a')
            if -1 == pos[ch]: pos[ch] = i
            elif distance[ch] + 1 != i - pos[ch]: return False
        return True