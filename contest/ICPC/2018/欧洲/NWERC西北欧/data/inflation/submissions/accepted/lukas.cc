//Solution by lukasP (Lukáš Poláček)
#include <algorithm>
#include <vector>
#include <cstdio>

#define rep(i,a,b) for(__typeof(b) i=(a); (i)<(b); ++(i))

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> c(n);
  rep(i,0,n) {
    scanf("%d", &c[i]);
  }

  std::sort(c.begin(), c.end());
  double min = 1;
  bool ok = true;
  rep(i,0,n) {
    if (c[i] > i + 1) {
      ok = false;
    }
    min = std::min(min, c[i] / double(i + 1));
  }
  if (ok) {
    printf("%.9lf\n", min);
  } else {
    printf("impossible\n");
  }
}
