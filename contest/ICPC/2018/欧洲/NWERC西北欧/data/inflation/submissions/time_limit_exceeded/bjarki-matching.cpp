#include <bits/stdc++.h>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;

#define MAXN 400000
int dist[MAXN+1], q[MAXN+1];
#define dist(v) dist[v == -1 ? MAXN : v]
struct bipartite_graph {
  int N, M, *L, *R; vi *adj;
  bipartite_graph(int _N, int _M) : N(_N), M(_M),
    L(new int[N]), R(new int[M]), adj(new vi[N]) {}
  ~bipartite_graph() { delete[] adj; delete[] L; delete[] R; }
  bool bfs() {
    int l = 0, r = 0;
    rep(v,0,N) if(L[v] == -1) dist(v) = 0, q[r++] = v;
      else dist(v) = INF;
    dist(-1) = INF;
    while(l < r) {
      int v = q[l++];
      if(dist(v) < dist(-1)) {
        iter(u, adj[v]) if(dist(R[*u]) == INF)
          dist(R[*u]) = dist(v) + 1, q[r++] = R[*u]; } }
    return dist(-1) != INF; }
  bool dfs(int v) {
    if(v != -1) {
      iter(u, adj[v])
        if(dist(R[*u]) == dist(v) + 1)
          if(dfs(R[*u])) {
            R[*u] = v, L[v] = *u;
            return true; }
      dist(v) = INF;
      return false; }
    return true; }
  void add_edge(int i, int j) { adj[i].push_back(j); }
  int maximum_matching() {
    int matching = 0;
    memset(L, -1, sizeof(int) * N);
    memset(R, -1, sizeof(int) * M);
    while(bfs()) rep(i,0,N)
      matching += L[i] == -1 && dfs(i);
    return matching; } };

int main() {
    int n;
    cin >> n;
    vi s(n);
    rep(i,0,n) {
        cin >> s[i];
    }

    double lo = 0,
           hi = 1.0,
           res = -1.0;
    while (abs(hi-lo) > 1e-8) {
        double f = (lo+hi)/2;
        bipartite_graph G(n, n);
        rep(i,0,n) {
            rep(j,0,n) {
                if (s[j] <= i+1 && s[j]+1e-8 >= (i+1) * f) {
                    G.add_edge(i, j);
                }
            }
        }
        if (G.maximum_matching() == n) {
            res = f;
            lo = f;
        } else {
            hi = f;
        }
    }
    if (res < -0.5) {
        cout << "impossible" << endl;
    } else {
        cout << setprecision(10) << res << endl;
    }

    return 0;
}

