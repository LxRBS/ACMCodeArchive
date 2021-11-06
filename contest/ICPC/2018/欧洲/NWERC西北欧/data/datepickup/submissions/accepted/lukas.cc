// Solution by lukasP (Lukáš Poláček)
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

#define rep(i, a, b) for (__typeof(b) i = (a); (i) < (b); ++(i))

using graph_t = std::vector<std::vector<std::pair<int, int>>>;
constexpr int64_t kMax = 1LL << 50;
constexpr int kActive = 1 << 25;
constexpr int kPack = (1 << 17) - 1;
int64_t a, b;

std::vector<int64_t> calc_distances(const std::vector<std::pair<int, int64_t>>& d,
                                    const graph_t& graph) {
  std::priority_queue<int64_t, std::vector<int64_t>, std::greater<>> best;
  std::vector<int64_t> dist(graph.size(), kMax);
  for (const auto& pair : d) {
    best.emplace((pair.second << 17) | pair.first);
    dist[pair.first] = pair.second;
  }
  std::vector<bool> seen(graph.size(), false);
  while (!best.empty()) {
    int64_t d = best.top() >> 17;
    int cur = best.top() & kPack;
    best.pop();
    if (seen[cur]) continue;
    seen[cur] = true;
    for (const auto& pair : graph[cur]) {
      if (d + pair.second < dist[pair.first]) {
        dist[pair.first] = d + pair.second;
        best.emplace((dist[pair.first] << 17) | pair.first);
      }
    }
  }
  return dist;
}

std::vector<int64_t> distances;
std::vector<int64_t> r_distances;

bool valid(int64_t wait_time, const graph_t& graph) {
  std::vector<int64_t> dist(graph.size(), -1);
  std::vector<std::pair<int, int64_t>> starts;
  graph_t reachable(graph.size());
  rep(i, 0, graph.size()) if (r_distances[i] <= wait_time &&
                              distances[i] + r_distances[i] <= a + wait_time) {
    dist[i] = wait_time - r_distances[i];
    starts.emplace_back(i, dist[i]);
  }

  rep(i, 0, graph.size()) {
    for (const auto& pair : graph[i]) {
      if (r_distances[pair.first] + pair.second <= wait_time) {
        reachable[i].push_back(pair);
      }
    }
  }

  std::vector<int> in_deg(graph.size());
  {
    std::vector<int64_t> active_dist = calc_distances(starts, reachable);
    rep(i, 0, graph.size()) {
      if (active_dist[i] <= b - a) {
        in_deg[i] |= kActive;
        for (const auto& pair : reachable[i]) ++in_deg[pair.first];
      }
    }
  }

  std::queue<int> q;
  for (const auto& pair : starts) {
    if (in_deg[pair.first] == kActive) {  // in-degree == 0
      q.push(pair.first);
    }
  }

  for (; !q.empty(); q.pop()) {
    int u = q.front();
    for (const auto& pair : reachable[u]) {
      dist[pair.first] = std::max(dist[pair.first], dist[u] + pair.second);
      if (--in_deg[pair.first] == kActive) {
        q.push(pair.first);
      }
    }
  }

  // Find cycles
  if (std::any_of(in_deg.begin(), in_deg.end(),
                  [](const int deg) { return (deg & (kActive - 1)) > 0; })) {
    return true;
  }

  return std::any_of(dist.begin(), dist.end(), [](const int64_t d) { return d >= b - a; });
}

int main() {
  scanf("%ld %ld", &a, &b);
  int n, m;
  scanf("%d %d", &n, &m);

  std::vector<std::vector<std::pair<int, int>>> graph(n);
  std::vector<std::vector<std::pair<int, int>>> r_graph(n);
  rep(i, 0, m) {
    int u, v, t;
    scanf("%d %d %d", &u, &v, &t);
    --u;
    --v;
    graph[u].emplace_back(v, t);
    r_graph[v].emplace_back(u, t);
  }
  distances = calc_distances({{0, 0}}, graph);
  r_distances = calc_distances({{graph.size() - 1, 0}}, r_graph);

  int64_t start = std::max(int64_t{0}, distances[n - 1] - a) - 1, end = distances[n - 1];
  while (start + 1 < end) {
    int64_t mid = (start + end) / 2;
    if (valid(mid, graph))
      end = mid;
    else
      start = mid;
  }
  std::cout << end << std::endl;
}
