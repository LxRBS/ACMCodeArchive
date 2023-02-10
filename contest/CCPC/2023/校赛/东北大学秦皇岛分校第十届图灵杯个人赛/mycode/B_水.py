'''
判断一个四位数是否前两位后两位和相等
'''
t = int(input())
for kase in range(t):
    s = input()
    print('YES' if int(s[0:1]) + int(s[1:2]) == int(s[2:3]) + int(s[3:4]) else 'NO')