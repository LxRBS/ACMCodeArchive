/**
 *    author:  tourist
 *    created: 21.10.2018 12:57:00       
**/
#include <bits/stdc++.h>

using namespace std;

const int md = 998244353;

inline void add(int &a, int b) {
  a += b;
  if (a >= md) a -= md;
}

inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) a += md;
}

inline int mul(int a, int b) {
  return (int) ((long long) a * b % md);
}

inline int power(int a, long long b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

class dsu {
  public:
  vector<int> p;
  int n;

  dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
  }
  vector<vector<int>> c(n + 1, vector<int>(n + 1, 0));
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0) c[i][j] = 1; else
      if (i == 0) c[i][j] = 0;
      else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % md;
    }
  }
  vector<vector<int>> sti(n + 1, vector<int>(n + 1, 0));
  sti[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      sti[i][j] = sti[i - 1][j - 1];
      add(sti[i][j], mul(sti[i - 1][j], j));
    }
  }
  vector<int> bell(n + 1, 0);
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      add(bell[i], sti[i][j]);
    }
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    x--; y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<int> with(1 << k);
  vector<int> mp(n, 0);
  for (int mask = 0; mask < (1 << k); mask++) {
    dsu d(n);
    for (int i = 0; i < n; i++) {
      if (((mask >> a[i]) & 1) == 1) {
        for (int j : g[i]) {
          if (((mask >> a[j]) & 1) == 1) {
            d.unite(i, j);
          }
        }
      }
    }
    for (int i = 0; i < n; i++) {
      mp[i] = 0;
    }
    for (int i = 0; i < n; i++) {
      if (((mask >> a[i]) & 1) == 1) {
        mp[d.get(i)]++;
      }
    }
    with[mask] = 1;
    for (int comp : mp) {
      for (int i = 1; i <= comp; i++) {
        add(with[mask], mul(c[comp][i], bell[n - i]));
      }
    }
  }
  int ans = 0;
  for (int mask = 0; mask < (1 << k); mask++) {
    int bits = __builtin_popcount(mask);
    int cur = 0;
    for (int subset = 0; subset < (1 << k); subset++) {
      if ((mask & subset) == subset) {
        if (bits % 2 == __builtin_popcount(subset) % 2) {
          add(cur, with[subset]);
        } else {
          sub(cur, with[subset]);
        }
      }
    }
    for (int i = 0; i < bits; i++) {
      add(ans, mul(cur, power(2, k - i)));
    }
  }
  cout << ans << '\n';
  return 0;
}
