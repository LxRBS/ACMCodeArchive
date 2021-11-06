/**
 *    author:  tourist
 *    created: 19.10.2018 21:16:28       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int,int>>> g(n);
  vector<int> deg(n, 0);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    x--; y--;
    g[x].emplace_back(y, i);
    deg[y]++;
  }
  vector<int> order;
  for (int i = 0; i < n; i++) {
    if (deg[i] == 0) {
      order.push_back(i);
    }
  }
  for (int b = 0; b < (int) order.size(); b++) {
    for (auto &p : g[order[b]]) {
      int j = p.first;
      if (--deg[j] == 0) {
        order.push_back(j);
      }
    }
  }
  assert((int) order.size() == n);
  vector<int> pos(n);
  for (int i = 0; i < n; i++) {
    pos[order[i]] = i;
  }
  vector<char> res(m, '.');
  const int MAGIC = 43;
  for (int i = 0; i < n; i++) {
    for (auto &p : g[i]) {
      int j = p.first;
      int x = pos[i], y = pos[j];
      int cc = 0;
      while (x != y) {
        cc++;
        x /= MAGIC;
        y /= MAGIC;
      }
      res[p.second] = "RGB"[cc - 1];
    }
  }
  for (int i = 0; i < m; i++) {
    cout << res[i] << '\n';
  }
  return 0;
}
