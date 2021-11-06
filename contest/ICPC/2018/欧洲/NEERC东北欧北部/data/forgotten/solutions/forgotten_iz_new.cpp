#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

void add(int &x, ll y) {
  x = (x + y) % MOD;
}

int mul(int a, int b) {
  return 1LL * a * b % MOD;
}

int rev(int x, int m) {
  if (x == 1) return 1;
  return (1 - rev(m % x, x) * (ll)m) / x + m;
}

int solve(int n, int k, vector<int> a, vector<vector<int>> e) {
  vector<int> q, vis(n), par(n, -1);
  q.push_back(0);
  vis[0] = 1;
  for (int i = 0; i < n; i++) {
    for (int to : e[q[i]]) {
      if (!vis[to]) {
        q.push_back(to);
        par[to] = q[i];
        vis[to] = 1;
      }
    }
  }
  reverse(q.begin(), q.end());

  vector<int> fct(n + 1), ofct(n + 1);
  fct[0] = 1;
  for (int i = 1; i <= n; i++) fct[i] = mul(fct[i - 1], i);
  ofct[n] = rev(fct[n], MOD);
  for (int i = n - 1; i >= 0; i--) ofct[i] = mul(ofct[i + 1], i + 1);
  auto getC = [&](int N, int K) {
    return mul(fct[N], mul(ofct[K], ofct[N - K]));
  };

  vector<int> b(n + 1);
  b[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      add(b[i], mul(b[j], getC(i - 1, j)));
    }
  }

  vector<int> d(1 << k);
  for (int mask = 1; mask < (1 << k); mask++) {
    vector<int> sz(n);
    vector<int> cnt(n + 1);
    for (int v : q) {
      if (!(mask & (1 << a[v]))) continue;
      sz[v]++;
      if (par[v] == -1 || !(mask & (1 << a[par[v]]))) {
        for (int i = 1; i <= sz[v]; i++) {
          add(cnt[i], getC(sz[v], i));
        }
      } else {
        sz[par[v]] += sz[v];
      }
    }
    for (int i = 1; i <= n; i++) {
      add(d[mask], mul(cnt[i], b[n - i]));
    }
  }
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < (1 << k); j++) {
      if (j & (1 << i)) continue;
      add(d[j | (1 << i)], MOD - d[j]);
    }
  }
  int ans = 0;
  for (int mask = 0; mask < (1 << k); mask++) {
    int coef = 0, bits = __builtin_popcount(mask);
    for (int i = 0; i < bits; i++) coef += 1 << (k - i);
    add(ans, mul(coef, d[mask]));
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
