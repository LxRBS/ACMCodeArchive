"""
  1~9��9�����֣�ÿ��������һ������
  �ٸ���һ��n��ʾ����Ǯ��
  �ʣ���nȥ�����֣������Ժ�������������ܹ��õ��������Ƕ���
  ��Ȼ��������Խ��Խ�ã���������ͬ������£�����Խ��Խ��
  ��������ȫ����+�������
  ���ǵ����ı����ᳬʱ������n�ܴ�������
  ��������Ӧ�ðѴ�����С������ѡ�ܶ�飬ֻ�нӽ�������£�������̰��
  ������̰�ģ��ٱ���
"""

class Solution:
    def add(self, a, b):
        return a[0] + b[0], a[1] + b[1]

    def cmp(self, a, b):
        return a[0] < b[0] or (a[0] == b[0] and a[1] < b[1])

    def completeKnapsack(self, d, maxv, cost, gain, index, path):
        for v in range(cost, maxv+1):
            if self.cmp(d[v], self.add(d[v-cost], gain)):  # ��ʾҪѡ��index��
                path[index][v] = 1
                d[v] = self.add(d[v-cost], gain)
            else:  # ��ʾ����ѡ
                path[index][v] = 0


    def min(self, a):
        k, minn = 8, a[8]
        for i in range(7, -1, -1):
            if a[i] < minn:
                k, minn = i, a[i]
        return k, minn

    def solve(self, n, a):
        k, minn = self.min(a)
        if n < minn: return "-1"
        if 0 == n % minn: return "".join([str(k+1) for i in range(n//minn)])

        total = sum(a)
        left = n - total - total
        otherans = None
        if left >= minn:
            otherans = "".join([str(k+1) for i in range(left//minn)])
            n = n - (left//minn) * minn

        self.ans = ""
        d = [(0, 0) for i in range(n+1)]  # (����, ֵ)
        path = [[0 for j in range(n+1)] for i in range(9)]
        for i, ai in enumerate(a):
            self.completeKnapsack(d, n, ai, (1, i+1), i, path)
        self.output(a, 8, n, path)
        if otherans is not None:
            mid = None
            t = ord(otherans[0])
            for i, si in enumerate(self.ans):
                if t >= ord(si):
                    mid = i
                    break
            if mid is not None:
                self.ans = self.ans[0:mid] + otherans + self.ans[mid::]
            else:
                self.ans = self.ans + otherans
        return self.ans

    def output(self, a, index, cost, path):
        if index < 0: return ""
        if path[index][cost] != 0:
            self.ans = self.ans + str(index+1)
            self.output(a, index, cost-a[index], path)
        else:
            self.output(a, index-1, cost, path)