#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> len;
vector<int> to;
vector<int> c;
vector<int> ts;
vector<bool> used;

void dfs(int v) {
  if (used[v]) return;
  used[v] = true;
  for (int id: g[v]) {
    dfs(to[id]);
  }
  ts.push_back(v);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  g.resize(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(i);
    to.push_back(b);
    c.push_back(-1);
  }
  used = vector<bool>(n, false);
  for (int i = 0; i < n; i++) dfs(i);
  while (true) {
    vector<int> color(n);
    for (int i = 0; i < n; i++) {
      color[i] = rand() % 3;
    }
    for (int i = 0; i < n; i++) {
      for (int j : g[i]) {
        c[j] = color[i];
      }
    }
    len = vector<vector<int>>(3, vector<int>(n, -1));
    bool fail = false;
    for (int v : ts) {
      for (int i = 0; i < 3; i++) {
        len[i][v] = 0;
        for (int id : g[v]) {
          if (c[id] == i) {
            len[i][v] = max(len[i][v], len[i][to[id]] + 1);
          }
        }
        if (len[i][v] > 42) {
          fail = true;
          break;
        }
      }
      if (fail) break;
    }
    if (!fail) {
      for (int i = 0; i < m; i++) {
        printf("%c\n", "RGB"[c[i]]);
      }
      return 0;
    }
  }
}
