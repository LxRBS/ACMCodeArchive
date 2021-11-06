#include <iostream>
using namespace std;
#define int int64_t

struct rectangle {
  int x1, y1, x2, y2;
  int area() const { return (x2-x1)*(y2-y1); }
};
istream& operator>>(istream& is, rectangle& r) {
  return is >> r.x1 >> r.y1 >> r.x2 >> r.y2;
}

signed main() {
  int t; cin >> t;
  while (t--) {
    rectangle a, b;
    cin >> a >> b;
    int w = min(a.x2, b.x2) - max(a.x1, b.x1);
    int h = min(a.y2, b.y2) - max(a.y1, b.y1);
    int best = max(a.area(), b.area());
    if (w >= 0 && h >= 0) {
      best = max(best, rectangle{0, min(a.y1, b.y1),
                                   w, max(a.y2, b.y2)}.area());
      best = max(best, rectangle{0, min(a.x1, b.x1),
                                   h, max(a.x2, b.x2)}.area());
    }
    cout << best << '\n';
  }
}