#!/usr/bin/env python
import sys

dirs = {'U': (0, 1), 'D': (0, -1), 'L': (-1, 0), 'R': (1, 0)}

steps = raw_input()

ans = raw_input()
if ans == 'impossible':
    print 'impossible, skipping'
    sys.exit(1)

(sx, sy) = map(int, ans.split())
n = int(raw_input())
blocks = [tuple(map(int, raw_input().split())) for _ in range(n)]

xMin = xMax = 0
yMin = yMax = 0

for (x, y) in [(sx, sy)] + blocks:
    xMin = min(xMin, x)
    yMin = min(yMin, y)
    xMax = max(xMax, x)
    yMax = max(yMax, y)

if xMax-xMin > 100 or yMax-yMin > 100:
    print 'too large bounding box (%d,%d) - (%d,%d), skipping' % (xMin, yMin, xMax, yMax)
    sys.exit(1)

block_latex = '\n'.join('  \\filldraw [brown,draw=black!75] (%d,%d) rectangle++(1,1);' % (x, y) for (x, y) in blocks)

blocks = set(blocks)

path_latex = []
collision_latex = []
x, y = sx, sy
for step in steps:
    dx, dy = dirs[step]
    ox, oy = x, y
    while (x, y) != (0, 0) and (x+dx, y+dy) not in blocks:
        x += dx
        y += dy
    path_latex.append('   \draw[line width=0.25mm,-stealth,teal] (%.2f,%.2f) -- (%.2f,%.2f);' %
                      ((ox+0.5+0.1*dx+0.05*dy,
                        oy+0.5+0.1*dy+0.05*dx,
                        x+0.5-0.1*dx+0.05*dy,
                        y+0.5-0.1*dy+0.05*dx)))
    if (x, y) != (0, 0):
        collision_latex.append('   \draw [fill=red,draw=white] (%.2f,%.2f) circle (0.09);' % (x+0.5, y+0.5))


path_latex = '\n'.join(path_latex)
collision_latex = '\n'.join(collision_latex)


templ = open('visualize.template', 'r').read()


with open('visualize-tmp/fig.tex', 'w') as out:
    out.write(templ % locals())

# %% Route taken
# \begin{scope}[
#   very thick,
#   decoration={
#     markings,
#     mark=at position 0.025 with {\arrow{stealth}},
#     mark=at position 0.075 with {\arrow{stealth}},
#     mark=at position 0.200 with {\arrow{stealth}},
#     mark=at position 0.350 with {\arrow{stealth}},
#     mark=at position 0.450 with {\arrow{stealth}},
#     mark=at position 0.550 with {\arrow{stealth}},
#     mark=at position 0.650 with {\arrow{stealth}},
#     mark=at position 0.785 with {\arrow{stealth}},
#     mark=at position 0.925 with {\arrow{stealth}},
#   }]
#   \draw[line width=0.25mm,->,blue,postaction={decorate}]
#        (-2.5,  1.1)
#     -- (-2.5,  0.5)
#     -- (-3.5,  0.5)
#     -- (-3.5, -1.6)
#     -- (-5.5, -1.6) arc(-180:-270:0.2)
#     -- (-5.3, -1.4)
#     -- (-1.5, -1.4)
#     -- (-1.5,  0.5)
#         %% Falling into the hole.
#         -- (0.05, 0.5)
#         arc(90:68:1.2);
# \end{scope}
