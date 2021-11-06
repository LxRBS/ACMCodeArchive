import sys
s = raw_input()
max_c = max_r = r = c = 0
blocks = set()
vis = set()
p = 'X'
for d in s:
    vis.add((c,r))
#    print d, r, c, min_r, min_c, max_r, max_c
    if d in 'LR':
        if p not in 'LR':
            max_c += 10**7
            blocks.add((-max_c, r))
            blocks.add((max_c, r))
        c = -max_c + 1 if d == 'L' else max_c - 1
    else:
        if p not in 'UD':
            max_r += 10**7
            blocks.add((c, -max_r))
            blocks.add((c, max_r))
        r = -max_r + 1 if d == 'D' else max_r - 1
    p = d
if (c, r) in vis:
    sys.stdout.write('imPOSSible')
else:
    print -c
    print -r
    print len(blocks)
    print
    print '\n'.join(['%d \t %d' % (bc-c, br-r) for (bc, br) in blocks])
