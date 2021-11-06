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
  len = vector<vector<int>>(3, vector<int>(n));
  vector<int> color(n);
  for (int v : ts) {
    len[0][v] = len[1][v] = len[2][v] = 0;
    for (int id : g[v]) {
      c[id] = color[to[id]];
      len[c[id]][v] = max(len[c[id]][v], len[c[id]][to[id]] + 1);
    }
    color[v] = 0;
    if (len[1][v] < len[color[v]][v]) color[v] = 1;
    if (len[2][v] < len[color[v]][v]) color[v] = 2;
  }
  for (int i = 0; i < m; i++) {
    printf("%c\n", "RGB"[c[i]]);
  }
}
