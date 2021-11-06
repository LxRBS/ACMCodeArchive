#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

int n, m;
vector <vector <int>> G;
vector <int> T;
vector <pair <int, int>> ans;

int dfs(int v, int p) {
  T[v] = 1;
  int q = -1, b = -1, r;
  for (int w : G[v]) {
    if (w == p) continue;
    switch (T[w]) {
      case 0:
        r = dfs(w, v);
        if (r >= 0) {
          if (r != v) {assert(q < 0); q = r;}
        } else if (r == -n - 1) {
          if (b >= 0) ans.push_back(make_pair(b + 1, w + 1)), b = -1; else b = w;
        } else {
          ans.push_back(make_pair(-r, v + 1));
        }
        break;
      case 1:
        assert(q < 0);
        q = w;
        break;
    }
  }
  T[v] = 2;
  if (q >= 0) return q;
  if (b >= 0) return -b - 1;
  return -n - 1;
}

int main() {
  while (scanf("%d%d", &n, &m) == 2 && n) {
    G = vector <vector <int>>(n);
    T = vector <int>(n);
    ans = vector <pair <int, int>>();
    for (int i = 0; i < m; i++) {
      int k, p = -1;
      scanf("%d", &k);
      for (int j = 0; j < k; j++) {
        int v;
        scanf("%d", &v);
        v--;
        if (j) {
          G[p].push_back(v);
          G[v].push_back(p);
        }
        p = v;
      }
    }
    dfs(0, -1);
    printf("%lu\n", ans.size());
    for (auto p : ans) printf("%d %d\n", p.first, p.second);
  }
}
