size(1000);
defaultpen(0.5);
bbox(white, Fill);

int n = stdin;
int edges[];
for (int i = 0; i < 2*(n-1); ++i) {
  int a = stdin;
  edges.push(a-1);
}

pair pos[];
for (int i = 0; i < n; ++i) {
  real x = stdin, y = stdin;
  pos.push((x, y));
  dot((x, y));
}

for (int i = 0; i < n-1; ++i) {
  int a = edges[2*i], b = edges[2*i+1];
  draw(pos[a]--pos[b]);
}

shipout(bbox(xmargin=10, white, Fill));
