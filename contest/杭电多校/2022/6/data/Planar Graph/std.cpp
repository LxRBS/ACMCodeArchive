#include<bits/stdc++.h>
using namespace std;

const int _ = 1e5 + 5;
const int __ = 2e5 + 5;

int n, m;

int p[_];
bool vis[__];
int u[__], v[__];

int dsu(int x) {
  return p[x] == x ? x : p[x] = dsu(p[x]);
}

int main() {
  #ifdef Sakuyalove
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
  #endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    memset(vis, 0, sizeof vis);
    memset(p, 0, sizeof p);
    memset(u, 0, sizeof u);
    memset(v, 0, sizeof v);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      p[i] = i;
    }
    for (int i = 1; i <= m; i++) {
      cin >> u[i] >> v[i];
    }
    int tot = m;
    for (int i = m; i >= 1; i--) {
      int x = dsu(u[i]), y = dsu(v[i]);
      if (x != y) {
        tot--;
        vis[i] = 1;
        p[x] = y;
      }
    }
    cout << tot << endl;
    for (int i = 1; i <= m; i++) {
      if (!vis[i]) cout << i << ' ';
    }
    cout << endl;
  }
  return 0;
}