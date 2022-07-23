#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using uint = unsigned;
using pii = pair<int, int>;
const double eps = 1e-7;
const double PI = acos(-1);
const int MOD = 998244353; // 1e9+7;
// template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
const int INF = 1e9;
const int N = 2e5 + 7;
const int W = 1e2 + 7;

// 并查集模板
struct DSU {
  vector<int> fa;
  void init(int n) { fa = vector<int>(n+1); iota(fa.begin(), fa.end(), 0); }
  int get(int s) { return s == fa[s] ? s : fa[s] = get(fa[s]); }
  int& operator [] (int i) { return fa[get(i)]; }
  bool merge(int x, int y) { // merge x to y
    x = get(x); y = get(y);
    return x == y ? false : (fa[x] = y, true);
  }
};

DSU dsu;
int n, m;
int u[N], v[N], is_key_edge[N];
int _dfn, low[W], dfn[W];
vector<int> id_edges[N], sub_edges[N];
vector<int> vertex, valid_edges;
unordered_map<int, int> mp;
map<int, vector<int>> w_edges;

void build_sub_graph(vector<int> &edges) {
  mp.clear();
  vertex.clear();
  for (int i : edges) {
    vertex.emplace_back(u[i]);
    vertex.emplace_back(v[i]);
  }
  sort(vertex.begin(), vertex.end());
  vertex.erase(unique(vertex.begin(), vertex.end()), vertex.end());
  for (uint i = 0; i < vertex.size(); ++i) mp[vertex[i]] = i + 1;
}

void get_cutting_edge(int x, int fa = -1) {
  low[x] = dfn[x] = ++_dfn;
  for (int i : id_edges[x]) {
    int y = u[i] == x ? v[i] : u[i];
    if (dfn[y] == -1) {
      get_cutting_edge(y, i);
      low[x] = min(low[x], low[y]);
      if (low[y] > dfn[x]) is_key_edge[i] = 1;
    } else if (i != fa) {
      low[x] = min(low[x], dfn[y]);
    }
  }
}

// Tarjan 算法求桥边
void tarjan(vector<int> &edges) {
  #ifdef DEBUG
  // print_edges(edges);
  #endif
  build_sub_graph(edges);
  _dfn = -1;
  for (int i : edges) {
    int x = mp[u[i]];
    int y = mp[v[i]];
    low[x] = low[y] = -1;
    dfn[x] = dfn[y] = -1;
    id_edges[x].clear();
    id_edges[y].clear();
  }
  for (int i : edges) {
    id_edges[mp[u[i]]].emplace_back(i);
    id_edges[mp[v[i]]].emplace_back(i);
  }
  // tarjan
  for (int i : edges) {
    if (~dfn[i]) continue;
    get_cutting_edge(i, -1);
  }
}

// Stoer-Wagner 算法求 无向正权图 上的全局最小割问题
int stoer_wagner(vector<int> &edges) {
  static int dis[W][W];
  int s, t, n;
  int res = INF;
  vector<int> w, dap, ord, vis;

  #ifdef DEBUG
  print_edges(edges);
  #endif
  build_sub_graph(edges);
  n = vertex.size();
  dap = ord = vector<int>(n + 1, 0);
  for (int i = 1; i <= n; ++i) memset(dis[i] + 1, 0, sizeof(int) * n);
  for (int i : edges) {
    int x = mp[u[i]];
    int y = mp[v[i]];
    ++dis[x][y];
    ++dis[y][x];
  }

  function<int(int)> proc = [&](int x) {
    vis = vector<int>(n + 1, 0);
    w = vector<int>(n + 1, 0);
    w[0] = -1;
    for (int i = 1; i <= n-x+1; ++i) {
      int mx = 0;
      for (int j = 1; j <= n; ++j) {
        if (!dap[j] && !vis[j] && w[j] > w[mx]) mx = j;
      }
      vis[mx] = 1;
      ord[i] = mx;
      for (int j = 1; j <= n; ++j) {
        if (!dap[j] && ! vis[j]) w[j] += dis[mx][j];
      }
    }
    s = ord[n-x];
    t = ord[n-x+1];
    return w[t];
  };

  for (int i = 1; i < n; ++i) {
    res = min(res, proc(i));
    dap[t] = 1;
    for (int j = 1; j <= n; ++j) {
      dis[s][j] += dis[t][j];
      dis[j][s] += dis[j][t];
    }
  }
  return res;
}

inline void solve() {
  cin >> n >> m;
  int ans = m;
  dsu.init(n);
  w_edges.clear();
  memset(is_key_edge + 1, 0, sizeof(int) * m);

  for (int i = 1, w; i <= m; ++i) {
    cin >> u[i] >> v[i] >> w;
    w_edges[w].emplace_back(i);
  }

  for (auto it = w_edges.rbegin(); it != w_edges.rend(); ++it) {
    valid_edges.clear();
    for (int i : it->second) {
      u[i] = dsu[u[i]];
      v[i] = dsu[v[i]];
      if (u[i] == v[i]) continue;
      valid_edges.emplace_back(i);
    }
    if (valid_edges.empty()) continue;
    tarjan(valid_edges);
    // MST merge
    for (int i : valid_edges) dsu.merge(u[i], v[i]);
    // divide not_key_edge to sub_edges
    for (int i : valid_edges) {
      if (is_key_edge[i]) continue;
      int uf = dsu[u[i]];
      sub_edges[uf].emplace_back(i);
    }
    for (int i : valid_edges) {
      int uf = dsu[u[i]];
      if (sub_edges[uf].empty()) continue;
      ans = min(ans, stoer_wagner(sub_edges[uf]));
      sub_edges[uf].clear();
    }
  }

  int has_key_edge = accumulate(is_key_edge + 1, is_key_edge + m + 1, 0);
  if (has_key_edge) ans = 1;
  cout << ans << '\n';
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}