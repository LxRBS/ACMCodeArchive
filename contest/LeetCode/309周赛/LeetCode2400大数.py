"""
数轴起点为startPos，终点为endPos，问走k步恰好从起点到终点的方案总数是多少
首先要花endPos-startPos步，然后剩下的步数显然必须是偶数，且一半朝右一半朝左
令left = k - (endPos-startPos)
于是可知向正方向一共要走a=k-left/2步，向负方向一共要走b=left/2步，只要满足这个条件
就一定能走到，先走正还是先走负其实无所谓。所以本质上就是问a个+1和b个-1不同的排列总数是多少
再转化为其实就是问从a+b个位置选出b个位置设置成-1的方法数是多少，就是组合数C(a+b, b)
组合数可以用杨辉三角形计算(1000*1000够了)
也可以直接计算，python支持大数，所以可以算完了再取模，但是这样可能会比较慢，得看具体效果
这道题在LeetCode上是可以过的
"""

class Solution(object):
    def numberOfWays(self, startPos, endPos, k):
        """
        :type startPos: int
        :type endPos: int
        :type k: int
        :rtype: int
        """
        left = k - (endPos - startPos)
        if left < 0 or left % 2 == 1: return 0
        return self.C(k, left//2) % 1000000007

    def C(self, a, b): # ����C(a, b)
        return self.fac(a) // self.fac(b) // self.fac(a - b)
    def fac(self, n):
        ans = 1
        for i in range(1, n+1): ans *= i
        return ans