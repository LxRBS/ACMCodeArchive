//Solution by lukasP (Lukáš Poláček)
#include <cmath>
#include <complex>
#include <cstdio>
#include <vector>

#define rep(i,a,b) for(__typeof(b) i=(a); (i)<(b); ++(i))

using point = std::complex<double>;

std::vector<int> size;
std::vector<bool> seen;
std::vector<point> points;
void traverse(int node, const std::vector<std::vector<int>>& g) {
  size[node] = 1;
  seen[node] = true;
  for (const int& v : g[node]) if (!seen[v]) {
    traverse(v, g);
    size[node] += size[v];
  }
}

void draw(int node, point position, double left, double right, const std::vector<std::vector<int>>& g) {
  double border = left;
  double one = (right - left) / (size[node] - 1);
  points[node] = position;
  seen[node] = true;
  for (const int& v : g[node]) if (!seen[v]) {
    double new_border = border + one * size[v];
    draw(v, position + std::polar<double>(1, (border + new_border) / 2), border, new_border, g);
    border = new_border;
  }
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::vector<int>> g(n);
  rep(i,0,n - 1) {
    int a, b;
    scanf("%d %d", &a, &b);
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  size.resize(n);
  seen.resize(n);
  traverse(0, g);
  points.resize(n);
  seen.assign(n, false);
  draw(0, point(0, 0), -M_PI, M_PI,  g);

  rep(i,0,n) {
    printf("%.9lf %.9lf\n", real(points[i]), imag(points[i]));
  }
}
