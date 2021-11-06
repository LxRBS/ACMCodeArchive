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

void dfs(InStream &in, int v, int p) {
  L[v] = T[v] = ++tc;
  for (int w : G[v]) {
    if (w == p) continue;
    int sc = sp;
    if (T[w] <= T[v]) ST[sp++] = make_pair(v, w);
    in.ensuref(sp <= 3 * MAXN, "too many edges to be a cactus");
    if (!T[w]) {
      dfs(in, w, v);
      L[v] = min(L[v], L[w]);
      if (L[w] >= T[v]) {
        if (sp > sc + 1) {
          set <int> cur;
          int p = ST[sp - 1].second;
          for (int j = sc; j < sp; j++) {
            in.ensuref(ST[j].first == p, "each 2-connected component must be either a loop or a single edge");
            in.ensuref(cur.find(p) == cur.end(), "each 2-connected component must be either a loop or a single edge");
            cur.insert(p);
            p = ST[j].second;
          }
          in.ensuref(cur.size() == sp - sc, "each 2-connected component must be either a loop or a single edge");
        }
        sp = sc;
      }
    } else
      L[v] = min(L[v], T[w]);
  }
}

int dfs_s(InStream &in, int v, int p) {
  T[v] = 1;
  int q = -1, b = -1, r;
  for (int w : G[v]) {
    if (w == p) continue;
    switch (T[w]) {
      case 0:
        r = dfs_s(in, w, v);
        if (r >= 0) {
          if (r != v) {
            ensuref(q < 0, "re-check of cactus failed"); 
            q = r;
          }
        } else if (r == -n - 1) {
          in.ensuref(b < 0, "cactus is not strong - it's possible to add (%d, %d)", b + 1, w + 1);
          b = w;
        } else {
          in.ensuref(false, "cactus is not strong - it's possible to add (%d, %d)", -r, v + 1);
        }
        break;
      case 1:
        ensuref(q < 0, "re-check of cactus failed");
        q = w;
        break;
    }
  }
  T[v] = 2;
  if (q >= 0) return q;
  if (b >= 0) return -b - 1;
  return -n - 1;
}



int readAndCheck(InStream& in) {
  int a = in.readInt(0, 3 * n);
  for (int i = 0; i < a; i++) {
    int u = in.readInt(1, n) - 1;
    int v = in.readInt(1, n) - 1;
    in.ensuref(v != u, "loop at vertex %d", u + 1);
    in.ensuref(E.find(make_pair(v, u)) == E.end() && E.find(make_pair(u, v)) == E.end(), "duplicate edge (%d, %d)", u + 1, v + 1);
    E.insert(make_pair(v, u));
    E.insert(make_pair(u, v));
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs(in, 0, -1);
  for (int i = 0; i < n; i++) in.ensuref(T[i], "graph is not connected"); //this can't be, but cross-check
  T = vector <int>(n);
  dfs_s(in, 0, -1);
  return a;
}


int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
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
    vector <vector <int>> GB = G;
    set <pair <int, int>> EB = E;
    int pa = readAndCheck(ouf);
    G = GB, E = EB;
    int ja = readAndCheck(ans);
    if (ja < pa) {
        quitf(_wa, "participant has added more edges (%d) than jury (%d)", pa, ja);
    }
    if (ja > pa) {
        quitf(_fail, "jury has added more edges (%d) than participant (%d)", ja, pa);
    }
  }
  unsetTestCase();
  ensuref(nsum, "At least one case required");
  inf.readEof();
  quitf(_ok, "%d test cases", tcnt - 1);
}
