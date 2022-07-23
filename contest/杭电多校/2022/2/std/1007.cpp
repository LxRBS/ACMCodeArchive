#include <bits/stdc++.h>

using namespace std;

signed main() {
  int n, T;
  vector<pair<int, int>> t;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    t.resize(n + 1);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &t[i].first, &t[i].second);
    }
    t[n] = make_pair(1234567890, 0);
    sort(t.begin(), t.end());
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (t[i].second >= t[i + 1].first) break;
      ++ans;
    }
    printf("%d\n", ans);
  }
  return 0;
}