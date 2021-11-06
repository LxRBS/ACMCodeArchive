raw_input()
p = map(int, raw_input().split())

lead = p[0]
p[0] = -1<<60
p.sort()
gap = lead - p[-1] + 1
f = 1

steps = 0
while gap:
    inc = f.bit_length() - 1
    big = p[-1] - p[-2]
    if big*inc >= gap:
        steps += gap + (gap-1)/inc
        break
    gap -= inc*big
    steps += (inc+1)*big
    f += 1
    p.pop()

print (steps -1)
