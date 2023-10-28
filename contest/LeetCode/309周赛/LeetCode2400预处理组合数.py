"""
数轴起点为startPos，终点为endPos，问走k步恰好从起点到终点的方案总数是多少
首先要花endPos-startPos步，然后剩下的步数显然必须是偶数，且一半朝右一半朝左
令left = k - (endPos-startPos)
于是可知向正方向一共要走a=k-left/2步，向负方向一共要走b=left/2步，只要满足这个条件
就一定能走到，先走正还是先走负其实无所谓。所以本质上就是问a个+1和b个-1不同的排列总数是多少
再转化为其实就是问从a+b个位置选出b个位置设置成-1的方法数是多少，就是组合数C(a+b, b)
组合数可以用杨辉三角形计算(1000*1000够了)，直接在__init__计算就行了
这个是最慢的，因为每次都计算了10**6个组合数
"""

class Solution(object):
    mod = 1000000007 # ģ��
    c = [[1 for i in range(1001)] for j in range(1001)]
    def __init__(self): # ������Ǽ��������
        for i in range(1, 1001):
            for j in range(1, i):
                self.c[i][j] = (self.c[i-1][j] + self.c[i-1][j-1]) % self.mod

    def numberOfWays(self, startPos, endPos, k):
        """
        :type startPos: int
        :type endPos: int
        :type k: int
        :rtype: int
        """
        left = k - (endPos - startPos)
        if left < 0 or left % 2 == 1: return 0
        return self.c[k][left//2]