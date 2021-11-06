#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

void add(int &x, ll y) {
  x = (x + y) % MOD;
}

int solve(int n, int k, vector<int> a, vector<vector<int>> e) {
  struct item {
    vector<int> res, pref;
  };
  function<item(int, int)> dfs = [&](int v, int pr) {
    item cur;
    cur.res = vector<int>(1 << k, 0);
    cur.pref = vector<int>(1 << k, 1);
    vector<int> tmp = vector<int>(1 << k, 1);
    for (int to : e[v]) {
      if (to == pr) continue;
      auto nw = dfs(to, v);
      for (int mask = 0; mask < (1 << k); mask++) {
        cur.pref[mask] = (ll)cur.pref[mask] * nw.pref[mask] % MOD;
        add(tmp[mask], nw.pref[mask] - 1 + MOD);
        add(cur.res[mask], nw.res[mask]);
      }
    }
    for (int mask = 0; mask < (1 << k); mask++) {
      if (!(mask & (1 << a[v]))) {
        cur.pref[mask] = 1;
      } else {
        add(cur.pref[mask], cur.pref[mask]);
        add(cur.res[mask], cur.pref[mask] - tmp[mask] + MOD);
      }
    }
    return cur;
  };
  auto cur = dfs(0, -1);
  for (int t = 1; t < (1 << k); t <<= 1) {
    for (int i = 0; i < (1 << k); i += 2 * t) {
      for (int j = 0; j < t; j++) {
        add(cur.res[i + t + j], MOD - cur.res[i + j]);
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < (1 << k); i++) {
    int coef = 0;
    for (int j = 0; j < __builtin_popcount(i); j++) coef = (coef + (1 << (k - j))) % MOD;
    add(ans, (ll)cur.res[i] * coef);
  }
  return ans;
}

int main() {
#ifdef HOME
  freopen("in", "r", stdin);
#endif
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> a(n, -1);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]), a[i]--;
  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  cout << solve(n, k, a, e) << endl;
}
