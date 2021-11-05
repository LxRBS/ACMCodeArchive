size(1500);
defaultpen(1.8);
bbox(white, Fill);

real dst = stdin;
int cs = stdin;

int n = stdin;
path a;
for (int i = 0; i < n; ++i)
{
    real bx = stdin, by = stdin;
    pair p = (bx, by);
    if (size(a) == 0)
        a = p;
    else
        a = a -- p;
}

int m = stdin;
path b;
for (int i = 0; i < m; ++i)
{
    real bx = stdin, by = stdin;
    pair p = (bx, by);
    if (size(b) == 0)
        b = p;
    else
        b = b -- p;
}

int p = stdin;
path track;
for (int i = 0; i < p; ++i)
{
    real bx = stdin, by = stdin;
    pair p = (bx, by);
    if (size(track) == 0)
        track = p;
    else
        track = track -- p;
}

pen innerpen=white;
if (m > 15)
  innerpen=palered;
filldraw(b -- cycle, fillpen=lightgreen, drawpen=gray);
filldraw(a -- cycle, fillpen=innerpen, drawpen=gray);
draw(track, p=dashed+black+3);

shipout(bbox(xmargin=10, white, Fill));
