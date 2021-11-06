// Solution by lukasP (Lukáš Poláček)
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

#define rep(i, a, b) for (__typeof(b) i = (a); (i) < (b); ++(i))

constexpr int32_t kMax = 1 << 30;

std::vector<bool> seen;
int calc_root(const std::vector<int>& x, std::vector<int>& root, int v) {
  if (seen[v]) return root[v];
  root[v] = x[v];
  seen[v] = true;
  return root[v] = calc_root(x, root, x[v]);
}

int main() {
  int n;
  scanf("%d", &n);
  ++n;
  std::vector<int> x(n);
  int a[n][n];
  x[0] = 0;
  rep(i, 0, n) a[0][i] = 0;

  int64_t total = 0;
  std::vector<int> in_deg(n, 0);
  rep(i, 1, n) {
    int s;
    scanf("%d %d", &x[i], &s);
    ++in_deg[x[i]];
    total += s;
    rep(j, 0, n) {
      scanf("%d", &a[i][j]);
      a[i][j] -= s;
    }
  }

  std::vector<int> root(n, -2);
  std::vector<int> highest(n);
  std::queue<int> q;
  seen.assign(n, false);
  rep(i, 0, n) {
    highest[i] = i;
    if (!seen[i]) {
      calc_root(x, root, i);
    }
    if (in_deg[i] == 0) {
      q.push(i);
    }
  }

  for (; !q.empty(); q.pop()) {
    int u = q.front();
    int next = x[u];
    highest[next] = std::max(highest[next], highest[u]);
    if (--in_deg[next] == 0) {
      q.push(next);
    }
  }

  rep(i, 0, n) {
    // Process cycles
    if (root[i] == i) {
      int u = i;
      int best = kMax;
      do {
        highest[i] = std::max(highest[i], highest[u]);
        best = std::min(best, a[u][n - 1]);
        u = x[u];
      } while (u != i);
      total += best;

      u = i;
      do {
        highest[u] = highest[i];
        rep(j, 0, n) a[u][j] -= best;
        u = x[u];
      } while (u != i);
    }
  }

  std::vector<int64_t> quickest(n, kMax);
  quickest[highest[0]] = 0;
  rep(i, 0, n) if (quickest[i] < kMax) {
    rep(j, 1, n) if (i != j) {
      int end = highest[j];
      quickest[end] = std::min(quickest[end], quickest[i] + a[j][i]);
    }
  }
  std::cout << quickest[n - 1] + total << std::endl;
}
