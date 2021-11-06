/**
 *    author:  tourist
 *    created: 21.03.2021 03:19:32       
**/
#undef _GLIBCXX_DEBUG

#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> l(n), r(n);
  for (int i = 0; i < n; i++) {
    cin >> l[i] >> r[i];
  }
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return l[i] < l[j];
  });
  vector<int> roots;
  vector<int> st;
  vector<vector<int>> g(n);
  for (int i : order) {
    while (!st.empty() && l[i] > r[st.back()]) {
      st.pop_back();
    }
    if (st.empty()) {
      roots.push_back(i);
    } else {
      g[st.back()].push_back(i);
    }
    st.push_back(i);
  }
  vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2)));
  vector<vector<vector<int>>> pr(n, vector<vector<int>>(2, vector<int>(2)));
  vector<int> al(n), ar(n);
  function<void(int)> Dfs = [&](int i) {
    int sum = 0;
    for (int j : g[i]) {
      Dfs(j);
      sum += dp[j][0][0];
    }
    for (int x = 0; x < 2; x++) {
      for (int y = 0; y < 2; y++) {
        dp[i][x][y] = 0;
        if (g[i].empty()) {
          dp[i][x][y] = r[i] - l[i];
        } else {
          for (int p = 0; p <= (int) g[i].size(); p++) {
            int ft = sum;
            if (x == 1 || p == 0) {
              ft += l[g[i][0]] - l[i];
            }
            if (y == 1 || p == (int) g[i].size()) {
              ft += r[i] - r[g[i].back()];
            }
            if (p > 0 && p < (int) g[i].size()) {
              ft += l[g[i][p]] - r[g[i][p - 1]];
            }
            set<int> recalc;
            recalc.insert(0);
            recalc.insert((int) g[i].size() - 1);
            recalc.insert(p);
            recalc.insert(p - 1);
            for (int w : recalc) {
              if (w < 0 || w >= (int) g[i].size()) {
                continue;
              }
              ft -= dp[g[i][w]][0][0];
              int wx = ((w == 0 && x == 1) || w == p);
              int wy = ((w == (int) g[i].size() - 1 && y == 1) || w == p - 1);
              ft += dp[g[i][w]][wx][wy];
            }
            if (ft > dp[i][x][y]) {
              dp[i][x][y] = ft;
              pr[i][x][y] = p;
            }
          }
        }
      }
    }
  };
  function<void(int, int, int, int, int)> Restore = [&](int i, int x, int id_x, int y, int id_y) {
    if (g[i].empty()) {
      al[i] = l[i];
      ar[i] = r[i];
      return;
    }
    int p = pr[i][x][y];
    if (p > 0 && x != 0) {
      ar[id_x] = l[g[i][0]];
    }
    if (p < (int) g[i].size() && y != 0) {
      al[id_y] = r[g[i].back()];
    }
    al[i] = (p == 0 ? l[i] : r[g[i][p - 1]]);
    ar[i] = (p == (int) g[i].size() ? r[i] : l[g[i][p]]);
    for (int w = 0; w < (int) g[i].size(); w++) {
      int wx = ((w == 0 && x == 1) || w == p);
      int wid_x = (wx == 0 ? -1 : (w == p ? i : id_x));
      int wy = ((w == (int) g[i].size() - 1 && y == 1) || w == p - 1);;
      int wid_y = (wy == 0 ? -1 : (w == p - 1 ? i : id_y));
      Restore(g[i][w], wx, wid_x, wy, wid_y);
    }
  };
  int ans = 0;
  for (int x : roots) {
    Dfs(x);
    ans += dp[x][0][0];
    Restore(x, 0, -1, 0, -1);
  }
  int total = 0;
  for (int i = 0; i < n; i++) {
    assert(l[i] <= al[i] && al[i] < ar[i] && ar[i] <= r[i]);
    total += ar[i] - al[i];
  }
  assert(total == ans);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return al[i] < al[j];
  });
  for (int i = 0; i < n - 1; i++) {
    assert(ar[order[i]] <= al[order[i + 1]]);
  }
  cout << ans << '\n';
  for (int i = 0; i < n; i++) {
    cout << al[i] << " " << ar[i] << '\n';
  }
  return 0;
}
