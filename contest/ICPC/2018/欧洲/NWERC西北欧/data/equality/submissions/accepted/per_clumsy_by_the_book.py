#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**5)

class LOL:
    def __init__(self, typ, data):
        self.typ = typ
        self.data = data

    def elements(self, res):
        if self.typ == 0:
            res.extend(self.data)
        elif self.typ == 1:
            self.data[0].elements(res)
            self.data[1].elements(res)
        else:
            self.data.elements(res)

    def linearize(self, res):
        if self.typ == 0:
            if res and res[-1][1] == 0:
                res[-1][0].extend(self.data)
            else:
                res.append((self.data, 0))
        elif self.typ == 1:
            self.data[0].linearize(res)
            self.data[1].linearize(res)
        else:
            sub = []
            self.data.elements(sub)
            sub.sort()
            if sub[0] == sub[-1]: self.typ = 2
            if self.typ == 2 and res and res[-1][1] == 0:
                res[-1][0].extend(sub)
            else:
                res.append((sub, self.typ-2))

def parse(line):
    res = []
    tasks = [(0, None)]
    while tasks[0][1] is None:
        i = -1
        while tasks[i][1] is not None: i -= 1
        (at, res) = tasks[i]
        if line[at] == '[':
            L = []
            while line[at] != ']':
                at += 1
                v = 0
                while line[at].isdigit():
                    v = 10*v + int(line[at])
                    at += 1
                L.append(v)
            at += 1
            tasks[i] = (at, LOL(0, L))
        elif line[at] == 'c':
            if i == -1:
                tasks.append((at+7, None))
            elif i == -2:
                tasks.append((tasks[-1][0]+1, None))
            else:
                L = tasks[-2][1]
                R = tasks[-1][1]
                at = tasks[-1][0]
                tasks.pop()
                tasks.pop()
                tasks[-1] = (at+1, LOL(1, [L, R]))
        else:
            b = line[at+1] == 'h'
            if i == -1:
                tasks.append((at+7+b, None))
            else:
                (at, X) = tasks.pop()
                tasks[-1] = (at+1, LOL(2+b, X))
    return tasks[0][1]

P1 = parse(input())
P2 = parse(input())
Q1 = []
Q2 = []
P1.linearize(Q1)
P2.linearize(Q2)
print('%sequal' % (['not ', ''][Q1 == Q2]))
