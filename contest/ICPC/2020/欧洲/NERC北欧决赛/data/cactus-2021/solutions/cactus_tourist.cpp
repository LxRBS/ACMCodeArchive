/**
 *    author:  tourist
 *    created: 26.03.2021 19:02:08       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  while (n != 0 || m != 0) {
    vector<vector<pair<int, int>>> g(n);
    vector<int> edge_from, edge_to;
    auto Add = [&](int x, int y) {
      g[x].emplace_back(y, (int) edge_from.size());
      g[y].emplace_back(x, (int) edge_from.size());
      edge_from.push_back(x);
      edge_to.push_back(y);
    };
    for (int i = 0; i < m; i++) {
      int foo, last;
      cin >> foo >> last;
      --last;
      for (int j = 1; j < foo; j++) {
        int cur;
        cin >> cur;
        --cur;
        Add(last, cur);
        last = cur;
      }
    }
    m = (int) edge_from.size();
    vector<int> depth(n, -1);
    vector<int> pv(n, -1);
    vector<int> pe(n, -1);
    vector<int> min_depth(n, -1);
    vector<bool> marked(n, false);
    vector<bool> on_cycle(m, false);
    vector<bool> alone(m, false);
    function<void(int)> Dfs = [&](int v) {
      min_depth[v] = depth[v];
      for (auto& p : g[v]) {
        int to = p.first;
        int id = p.second;
        if (depth[to] == -1) {
          depth[to] = depth[v] + 1;
          pv[to] = v;
          pe[to] = id;
          Dfs(to);
          min_depth[v] = min(min_depth[v], min_depth[to]);
        } else {
          if (depth[to] < depth[v] - 1) {
            on_cycle[id] = true;
            min_depth[v] = min(min_depth[v], depth[to]);
          }
        }
      }
      if (pv[v] != -1) {
        if (min_depth[v] != depth[v]) {
          on_cycle[pe[v]] = true;
        } else {
          if (g[v].size() % 2 == 1 && g[pv[v]].size() % 2 == 1 && !marked[v] && !marked[pv[v]]) {
            alone[pe[v]] = true;
            marked[v] = true;
            marked[pv[v]] = true;
          }
        }
      }
    };
    depth[0] = 0;
    Dfs(0);
    vector<vector<int>> nei(m);
    for (int i = 0; i < n; i++) {
      vector<int> ids;
      for (auto& p : g[i]) {
        int id = p.second;
        if (!on_cycle[id] && !alone[id]) {
          ids.push_back(id);
        }
      }
      for (int j = 0; j + 1 < (int) ids.size(); j += 2) {
        nei[ids[j]].push_back(ids[j + 1]);
        nei[ids[j + 1]].push_back(ids[j]);
      }
    }
    vector<vector<int>> paths;
    vector<bool> used(m, false);
    for (int i = 0; i < m; i++) {
      if (!on_cycle[i] && !alone[i] && nei[i].empty()) {
        bool found = false;
        for (int end : {edge_from[i], edge_to[i]}) {
          for (auto& p : g[end]) {
            int id = p.second;
            if (!on_cycle[id] && alone[id]) {
              nei[i].push_back(id);
              nei[id].push_back(i);
              found = true;
              break;
            }
          }
          if (found) {
            break;
          }
        }
        if (!found) {
          alone[i] = true;
        }
      }
    }
    for (int i = 0; i < m; i++) {
      if (!on_cycle[i] && !used[i] && nei[i].size() == 1) {
        vector<int> path = {i, nei[i][0]};
        used[path[0]] = true;
        used[path[1]] = true;
        while (true) {
          int j = path.back();
          if (nei[j].size() == 1) {
            break;
          }
          assert(nei[j].size() == 2);
          int nxt = (nei[j][0] ^ nei[j][1] ^ path[path.size() - 2]);
          path.push_back(nxt);
          used[path.back()] = true;
        }
        paths.push_back(path);
      }
    }
    auto GetVertex = [&](int e1, int e2) {
      // for edges A-B and B-C returns A
      for (int x : {edge_from[e1], edge_to[e1]}) {
        if (x != edge_from[e2] && x != edge_to[e2]) {
          return x;
        }
      }
      assert(false);
      return -1;
    };
    cout << paths.size() << '\n';
    for (auto& path : paths) {
      int x = GetVertex(path[0], path[1]);
      int y = GetVertex(path.back(), path[path.size() - 2]);
      cout << x + 1 << " " << y + 1 << '\n';
    }
    cin >> n >> m;
  }
  return 0;
}
