#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

using int64 = std::int64_t;
static const int64 INF = std::numeric_limits<int64>::max() / 10;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vl = vector<int64>;

int64 Dijkstra(const vector<vector<pair<int, int64>>>& graph, int s, int t) {
  int n = graph.size();
  vl dists(n, INF);
  dists[s] = 0;
  priority_queue<pair<int64, int>, vector<pair<int64, int>>,
                 greater<pair<int64, int>>>
      open_nodes;
  open_nodes.emplace(0, s);
  vector<bool> closed(n, false);
  while (!open_nodes.empty()) {
    int64 dist;
    int node;
    std::tie(dist, node) = open_nodes.top();
    open_nodes.pop();
    if (closed[node]) continue;
    closed[node] = true;
    dists[node] = dist;
    for (const auto& edge : graph[node]) {
      if (closed[edge.first] || dist + edge.second >= dists[edge.first]) {
        continue;
      }
      dists[edge.first] = dist + edge.second;
      open_nodes.emplace(dist + edge.second, edge.first);
    }
  }
  return dists[t];
}

void AddEdge(vector<vector<pair<int, int64>>>* graph, int u, int v, int64 w) {
  graph->at(u).emplace_back(v, w);
}

int main() {
  int n, m, k1, k2;
  cin >> n >> m >> k1 >> k2;
  vvvi node_mapping(n, vvi(k1 + 1, vi(k2 + 2)));
  int next_id = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= k1; ++j) {
      for (int k = 0; k <= k2; ++k) {
        node_mapping[i][j][k] = next_id++;
      }
    }
  }
  vector<vector<pair<int, int64>>> graph(n * (k1 + 1) * (k2 + 1));
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    int64 x;
    cin >> u >> v >> x >> c;
    --u;
    --v;
    for (int j = 0; j <= k1; ++j) {
      for (int k = 0; k <= k2; ++k) {
        if (c == 0) {
          AddEdge(&graph, node_mapping[u][j][k], node_mapping[v][j][k], x);
          AddEdge(&graph, node_mapping[v][j][k], node_mapping[u][j][k], x);
        } else if (c == 1 && j < k1) {
          AddEdge(&graph, node_mapping[u][j][k], node_mapping[v][j + 1][k], x);
          AddEdge(&graph, node_mapping[v][j][k], node_mapping[u][j + 1][k], x);
        } else if (c == 2 && k < k2) {
          AddEdge(&graph, node_mapping[u][j][k], node_mapping[v][j][k + 1], x);
          AddEdge(&graph, node_mapping[v][j][k], node_mapping[u][j][k + 1], x);
        }
      }
    }
  }
  int s, t;
  cin >> s >> t;
  --s;
  --t;
  int64 ans = Dijkstra(graph, node_mapping[s][0][0], node_mapping[t][k1][k2]);
  if (ans == INF) ans = -1;
  cout << ans << endl;
  return 0;
}
