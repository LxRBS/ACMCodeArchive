#!/usr/bin/env python3

def my_eval(p):
    ignore = 0
    ans = ([], [])
    op = ''
    shuffle_ans = []
    i = 0
    while i < len(p):
        if p[i] == 'c':
            if op: ignore += 1
            i += 7
        elif p[i] == 's' and p[i+1] == 'o':
            if op: ignore += 1
            else:
                op = 'sort'
                shuffle_ans = []
            i += 7
        elif p[i] == 's' and p[i+1] == 'h':
            if op: ignore += 1
            else:
                op = 'shuffle'
                shuffle_ans = []
            i += 8
        elif p[i] == '[':
            j = p.index(']', i+1)
            l = list(map(int, p[i+1:j].split(',')))
            if op:
                shuffle_ans.extend(l)
            else:
                ans[0].extend(l)
                ans[1].extend(l)
            i = j+1
        elif p[i] == ',':
            i += 1
        elif p[i] == ')':
            if ignore > 0: ignore -= 1
            elif op:
                l = sorted(shuffle_ans);
                ans[0].extend(l)
                if op == 'shuffle':
                    ans[1].extend(l[::-1])
                else:
                    ans[1].extend(l)
                op = ''
                shuffle_ans = []
            i += 1
    return ans

p1, p2 = input(), input()
print('equal' if my_eval(p1) == my_eval(p2) else 'not equal')
