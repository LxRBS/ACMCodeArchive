#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include "testlib.h"

using namespace std;

const int MAXN = (int)1e5;
const int MAXM = (int)1e5;
const int MAXK = 1000;
int n, m, tc, sp, tcnt;

vector <vector <int>> G;
set <pair <int, int>> E;
vector <int> T, L;
pair <int, int> ST[3 * MAXN];

void dfs(int v, int p) {
  L[v] = T[v] = ++tc;
  for (int w : G[v]) {
    if (w == p) continue;
    int sc = sp;
    if (T[w] <= T[v]) ST[sp++] = make_pair(v, w);
    ensuref(sp <= 3 * MAXN, "too many edges to be a cactus");
    if (!T[w]) {
      dfs(w, v);
      L[v] = min(L[v], L[w]);
      if (L[w] >= T[v]) {
        if (sp > sc + 1) {
          set <int> cur;
          int p = ST[sp - 1].second;
          for (int j = sc; j < sp; j++) {
            ensuref(ST[j].first == p, "each 2-connected component must be either a loop or a single edge");
            ensuref(cur.find(p) == cur.end(), "each 2-connected component must be either a loop or a single edge");
            cur.insert(p);
            p = ST[j].second;
          }
          ensuref(cur.size() == sp - sc, "each 2-connected component must be either a loop or a single edge");
        }
        sp = sc;
      }
    } else
      L[v] = min(L[v], T[w]);
  }
}

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  int nsum = 0, msum = 0;
  while (1) {
    ++tcnt;
    setTestCase(tcnt);
    n = inf.readInt(0, MAXN, "number of vertices");
    inf.readSpace();
    m = inf.readInt(0, n ? MAXM : 0, "number of paths");
    inf.readEoln();
    nsum += n;
    msum += m;
    ensuref(nsum <= MAXN && msum <= MAXM, "too large test");
    G = vector <vector <int>>(n);
    E = set <pair <int, int>>();
    T = vector <int>(n);
    L = vector <int>(n);
    if (!n && !m) break;
    for (int i = 0; i < m; i++) {
      int k, p = -1;
      k = inf.readInt(2, MAXK, "path length");
      for (int j = 0; j < k; j++) {
        inf.readSpace();
        int v = inf.readInt(1, n, "vertex number") - 1;
        if (j) {
          ensuref(v != p, "loop at vertex %d", v + 1);
          ensuref(E.find(make_pair(v, p)) == E.end() && E.find(make_pair(p, v)) == E.end(), "duplicate edge (%d, %d)", v + 1, p + 1);
          E.insert(make_pair(v, p));
          E.insert(make_pair(p, v));
          G[p].push_back(v);
          G[v].push_back(p);
        }
        p = v;
      }
      inf.readEoln();
    }
    dfs(0, -1);
    for (int i = 0; i < n; i++) ensuref(T[i], "graph is not connected");
  }
  unsetTestCase();
  ensuref(nsum, "At least one case required");
  inf.readEof();
}
