#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  int n; double C;
  scanf("%d%lf", &n, &C);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = n - 1; i > 0; i--) {
    a[i] -= a[i-1];
  }
  a.erase(a.begin());
  --n;

  int positive = 0, negative = 0;
  for (int i = 0; i < n; i++) {
    long long s = a[i], s2 = a[i] * a[i];
    for (int j = i + 1; j < n; j++) {
      s += a[j];
      s2 += a[j] * a[j];
      long long den = (j - i + 1) * s2 - s * s;
      if (s != 0) {
        assert(den == 0 || fabs(abs(s) / sqrt(den) - C) > 1.5e-8);
        if (den == 0 || abs(s) / sqrt(den) >= C) {
          if (s > 0) {
            positive++;
          } else {
            negative++;
          }
        }
      }
    }
  }
  printf("%d %d\n", positive, negative);
}
