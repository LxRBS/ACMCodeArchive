"""
��������������������ڵ㷭ת
Ҳ�����ҳ����ѵ�˳�򣬽��䷭ת����
����Ҫ������Ŀ���������ݽṹ
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
        while True:  # ������Ĺ��ѣ����������ֲ�
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
        for i in range(1, len(a), 2): # �������㷭ת
            a[i].reverse()
        # ���½�ֵ���ɸ��ڵ�
        q.append(root)
        for ai in a:
            sz = len(q)
            assert sz == len(ai) # ����Ӧ�����
            for i in range(sz):
                h = q.popleft()
                h.val = ai[i]
                if h.left is not None:
                    q.append(h.left)
                    q.append(h.right)
        return root