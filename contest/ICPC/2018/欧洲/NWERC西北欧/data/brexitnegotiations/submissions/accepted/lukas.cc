//Solution by lukasP (Lukáš Poláček)
#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>

#define rep(i,a,b) for(__typeof(b) i=(a); (i)<(b); ++(i))

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::vector<int>> g(n);
  std::vector<int> e(n), in_deg(n);
  rep(i,0,n) {
    int d;
    scanf("%d %d", &e[i], &d);
    rep(j,0,d) {
      int b; scanf("%d", &b);
      g[i].push_back(b - 1);
      ++in_deg[b - 1];
    }
  }

  std::priority_queue<std::pair<int, int>> best;
  rep(i,0,n) if (in_deg[i] == 0) {
    best.emplace(-e[i], i);
  }

  int result = 0;
  for (int i = n - 1; i >= 0; --i) {
    int u = best.top().second;
    best.pop();
    result = std::max(result, e[u] + i);
    for (const int before : g[u]) {
      if (--in_deg[before] == 0) best.emplace(-e[before], before);
    }
  }
  printf("%d\n", result);
}
