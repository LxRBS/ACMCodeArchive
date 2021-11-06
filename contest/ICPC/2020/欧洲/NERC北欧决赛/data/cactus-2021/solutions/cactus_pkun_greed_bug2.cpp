#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

void remove_cycles(vector<vector<int>>& g) {
  vector<pair<int, int>> stack;
  vector<pair<int, int>> tree_edges;
  vector<int> used(g.size());
  auto dfs = [&](int v, int p, auto dfs) -> void {
    used[v] = 1;
    for (int u : g[v]) {
      if (u == p) continue;
      if (used[u] == 2) continue;
      if (used[u] == 1) {
        while (stack.back().first != u) stack.pop_back();
        stack.pop_back();
        continue;
      }
      stack.template emplace_back(v, u);
      dfs(u, v, dfs);
      if (!stack.empty() && stack.back() == pair<int,int>{v, u}) {
        tree_edges.template emplace_back(stack.back());
        stack.pop_back();
      }
    }
    used[v] = 2;
  };
  dfs(0, -1, dfs);
  g = vector<vector<int>>(g.size());
  for (auto [u, v] : tree_edges) {
    g[u].push_back(v);
    g[v].push_back(u);
  }
}

void solve(int n, int m) {
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int k;
    scanf("%d", &k);
    int last; scanf("%d", &last);
    for (int j = 1; j < k; j++) {
      int nxt;
      scanf("%d", &nxt);
      g[last - 1].push_back(nxt - 1);
      g[nxt - 1].push_back(last - 1);
      last = nxt;
    }
  }
  remove_cycles(g);

  vector<pair<int, int>> ans;

  vector<bool> used(n);
  auto build = [&](int v, int p, auto build) -> int {
    used[v] = true;
    bool skipped = false;
    int skipped_v = -1;
    int cur_from = -1;
    for (int u : g[v]) {
      if (u == p) continue;
      int from = build(u, v, build);
      if (from == -1) {
        if (skipped) {
          from = u;
        } else {
          skipped = true;
          skipped_v = u;
          continue;
        }
      }
      if (cur_from == -1) {
        cur_from = from;
      } else {
        ans.emplace_back(from, cur_from);
        cur_from = -1;
      }
    }
    if (cur_from == -1) {
      if (skipped && p != -1) {
        return skipped_v;
      } else {
        return -1;
      }
    } else {
      if (p == -1) {
        ans.emplace_back(cur_from, v);
        return -1;
      } else {
        return cur_from;
      }
    }
  };

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      int r = build(i, -1, build);
      assert(r == -1);
    }
  }

  printf("%d\n", (int)ans.size());
  for (auto [x, y] : ans) {
    printf("%d %d\n", x + 1, y + 1);
  }
}

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    if (n == 0 && m == 0) break;
    solve(n, m);
  }
}
