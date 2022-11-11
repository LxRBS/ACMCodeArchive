"""
完美二叉树，将奇数层节点翻转
也就是找出广搜的顺序，将其翻转即可
但是要符合题目给出的数据结构
"""

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right


class Solution(object):
    def reverseOddLevels(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        if root is None: return root
        q = collections.deque()
        q.append(root)
        a = []
        while True:  # 批处理的广搜，将二叉树分层
            sz = len(q)
            if 0 == sz: break
            tmp = []
            for i in range(sz):
                h = q.popleft()
                tmp.append(h.val)
                if h.left is not None:
                    q.append(h.left)
                    q.append(h.right)
            a.append(tmp)
        for i in range(1, len(a), 2): # 将奇数层翻转
            a[i].reverse()
        # 重新将值分派给节点
        q.append(root)
        for ai in a:
            sz = len(q)
            assert sz == len(ai) # 长度应该相等
            for i in range(sz):
                h = q.popleft()
                h.val = ai[i]
                if h.left is not None:
                    q.append(h.left)
                    q.append(h.right)
        return root