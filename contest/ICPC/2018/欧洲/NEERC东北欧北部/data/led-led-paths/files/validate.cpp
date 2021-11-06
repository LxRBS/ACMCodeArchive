#include "testlib.h"

using namespace std;

const int MAXN = 50000;
const int MAXM = 200000;

vector<vector<int>> g;
vector<int> used;

void dfs(int v) {
  ensure(used[v] != 1);
  if (used[v]) return;
  used[v] = 1;
  for (int u : g[v]) {
    dfs(u);
  }
  used[v] = 2;
}

int main(int argc, char **argv) {
  registerValidation(argc, argv);

  int n = inf.readInt(2, MAXN, "n");
  inf.readSpace();
  int m = inf.readInt(1, MAXM, "m");
  inf.readEoln();
  g.resize(n);
  for (int i = 0; i < m; i++) {
    int a = inf.readInt(1, n, "a[" + vtos(i) + "]") - 1;
    inf.readSpace();
    int b = inf.readInt(1, n, "b[" + vtos(i) + "]") - 1;
    inf.readEoln();
    g[a].push_back(b);
  }

  for (int i = 0; i < n; i++) {
    sort(g[i].begin(), g[i].end());
    ensure(unique(g[i].begin(), g[i].end()) == g[i].end());
  }

  used = vector<int>(n, 0);

  for (int i = 0; i < n; i++) {
    dfs(i);
  }

  inf.readEof();
  return 0;
}
