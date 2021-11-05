"""
  1~9的9个数字，每个数字有一个代价
  再给定一个n表示现有钱数
  问：用n去买数字，买完以后再组合起来，能够得到最大的数是多少
  显然数字数量越多越好，在数量相同的情况下，数字越大越好
  可以用完全背包+方案输出
  但是单纯的背包会超时，对于n很大的情况，
  毫无疑问应该把代价最小的数字选很多遍，只有接近的情况下，不能再贪心
  所以先贪心，再背包
"""

class Solution:
    def add(self, a, b):
        return a[0] + b[0], a[1] + b[1]

    def cmp(self, a, b):
        return a[0] < b[0] or (a[0] == b[0] and a[1] < b[1])

    def completeKnapsack(self, d, maxv, cost, gain, index, path):
        for v in range(cost, maxv+1):
            if self.cmp(d[v], self.add(d[v-cost], gain)):  # 表示要选第index个
                path[index][v] = 1
                d[v] = self.add(d[v-cost], gain)
            else:  # 表示不用选
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
        d = [(0, 0) for i in range(n+1)]  # (数量, 值)
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