#define _USE_MATH_DEFINES
#include <cassert>
#include <cmath>
#include <cstdio>
#include <optional>
#include <vector>
#include <cstdlib>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) (void)42
#endif

const double eps = 1e-9;

int sgn(double x) { return x < -eps ? -1 : x > eps; }
struct point {
  double x, y;
  point() : x(0), y(0) {}
  point(double x, double y) : x(x), y(y) {}
  point operator+(const point &p2) const {
    return point(x + p2.x, y + p2.y);
  }
  point operator-(const point &p2) const {
    return point(x - p2.x, y - p2.y);
  }
  point operator*(const double b) const {
    return point(x * b, y * b);
  }
  point operator/(const double b) const {
    return point(x / b, y / b);
  }
  double operator*(const point &p2) const {
    return x * p2.y - y * p2.x;
  }
  friend double sprod(const point &p1, const point &p2) {
    return p1.x * p2.x + p1.y * p2.y;
  }
  double dist2() const {
    return x * x + y * y;
  }
  double dist() const {
    return sqrt(dist2());
  }

  point normed() const {
    return *this / dist();
  }
  point ort() const {
    return {-y, x};
  }
};

struct line {
  double a, b, c;
  line() : a(0), b(0), c(1) {}
  line(const point &p1, const point &p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a * p1.x - b * p1.y;
  }
  line(double a, double b, double c) : a(a), b(b), c(c) {}
  double distz(const point &p) const { return a * p.x + b * p.y + c; }
  double norm2() const { return a * a + b * b; }
  double dists(const point &p) const { return distz(p) / sqrt(norm2()); }
  double dist(const point &p) const { return fabs(distz(p)) / sqrt(norm2()); }
  int side(const point &p2) const { return sgn(a * p2.x + b * p2.y + c); }
};

optional<point> intersect(const line &l1, const line &l2) {
  double d = l1.a * l2.b - l1.b * l2.a;
  if (fabs(d) < eps) {
    return {};
  }
  point res(
    (l1.b * l2.c - l1.c * l2.b) / d,
    (l1.a * l2.c - l1.c * l2.a) / -d);
#ifdef LOCAL
  assert(l1.side(res) == 0);
  assert(l2.side(res) == 0);
#endif
  return res;
}

point get_by_dist(point st, point sec, point v, double l) {
  v = v.normed();
  double lf = 0;
  double rg = l;
  for (int i = 0; i < 60; i++) {
    double m = (lf + rg) / 2;
    point p = st + v * m;
    if (m + (p - sec).dist() <= l) {
      lf = m;
    } else {
      rg = m;
    }
  }
  return st + v * lf;
}

struct Arc {
  // p + v1 * cos(a) + v2 * sin(a) with a from l to r
  point p, v1, v2;
  double l, r;

  Arc(point F1, point F2, double len, point A, point B) {
    p = (F1 + F2) / 2;
    auto v1n = (F2 - F1).normed();
    v1 = v1n * (len / 2);
    v2 = v1n.ort() * sqrt((len / 2) * (len / 2) - (F2 - p).dist2());
    l = get_angle(A);
    r = get_angle(B);
    if (r < l) {
      r += 2 * M_PI;
    }
#ifdef LOCAL
    assert((get_pt(l) - A).dist2() < eps);
    assert((get_pt(r) - B).dist2() < eps);
#endif
  }

  point get_pt(double ang) const {
    return p + v1 * cos(ang) + v2 * sin(ang);
  }

  double get_angle(point pt) const {
    double ca = sprod(pt - p, v1) / v1.dist2();
    double sa = sprod(pt - p, v2) / v2.dist2();
    return atan2(sa, ca);
  }

  double area() const {
    // 1/2 int f(t) x f'(t)
    // 1/2 int (p + v1 * cos + v2 * sin) x (-v1 * sin + v2 * cos)
    // 1/2 int -(p x v1) * sin + (p x v2) * cos + (v1 x v2) * cos^2 - (v2 x v1) * sin^2
    // 1/2 int -(p x v1) * sin + (p x v2) * cos + (v1 x v2)
    // 1/2 ((p x v1) * cos + (p x v2) * sin + (v1 x v2) * t)
    return ((p * v1) * (cos(r) - cos(l)) + (p * v2) * (sin(r) - sin(l)) + (v1 * v2) * (r - l)) / 2;
  }
};

int main() {
  int n; double l;
  while (scanf("%d%lf", &n, &l) == 2) {
    vector<point> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf", &v[i].x, &v[i].y);
    }

    l -= (v[0] - v.back()).dist();
    for (int i = 1; i < n; i++) {
      l -= (v[i] - v[i - 1]).dist();
    }

    int p2 = 0;
    while (true) {
      if (p2 == n - 1 || sgn((v[0] - v.back()) * (v[p2 + 1] - v[p2])) <= 0) {
        break;
      }
      auto p = intersect(line(v[0], v.back()), line(v[p2], v[p2 + 1]));
      if (!p) break;
      if ((*p - v[0]).dist() + (*p - v[p2]).dist() >= l) break;
      l += (v[p2 + 1] - v[p2]).dist();
      p2++;
    }

    point cur = get_by_dist(v[0], v[p2], v[0] - v.back(), l);

    auto get_pt = [&](int id) {
      return v[id % n];
    };

    vector<Arc> arcs;

    int p1 = 0;
    while (p1 < n) {
      auto P1 = get_pt(p1);
      auto P1N = get_pt(p1+1);
      auto P2 = get_pt(p2);
      auto P2N = get_pt(p2+1);
      point A = get_by_dist(P1, P2, P1N - P1, l);
      point B = get_by_dist(P2, P1, P2 - P2N, l);

      point next;
      double nl;
      if ((A - P2).dist() > (B - P2).dist()) {
        next = A;
        nl = l - (P1N - P1).dist();
        p1++;
      } else {
        next = B;
        nl = l + (P2N - P2).dist();
        p2++;
      }

      arcs.emplace_back(P1, P2, l, cur, next);
      cur = next;
      l = nl;
    }

    double tot_area = 0;
    for (const auto &arc : arcs) {
      tot_area += arc.area();
      eprintf("\\addplot [domain=%lf:%lf,samples=50]({%lf + %lf*cos(\\x) + %lf * sin(\\x)},{%lf + %lf*cos(\\x) + %lf * sin(\\x)}); \n",
              arc.l + 2 * M_PI, arc.r + 2 * M_PI, arc.p.x, arc.v1.x, arc.v2.x, arc.p.y, arc.v1.y, arc.v2.y);
    }
    printf("%.18lf\n", tot_area);
  }
}
