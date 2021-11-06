#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

void print_answer(const std::vector<int> &path) {
  assert(!path.empty());
  assert(path[0] == 0);
  std::cout << path.size() - 1U << '\n';
  for (int v : path) {
    std::cout << v + 1 << ' ';
  }
  std::cout << '\n';
}

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<std::set<int>> children(n);
  std::vector<int> parent(n, -1);
  for (int i = 1; i < n; i++) {
    int a;
    std::cin >> a;
    a--;
    assert(a < i);
    parent[i] = a;
    children[a].insert(i);
  }

  std::vector<int> depth(n);
  depth[0] = 0;
  for (int i = 1; i < n; i++) {
    depth[i] = depth[parent[i]] + 1;
  }

  const int end = std::max_element(depth.begin(), depth.end()) - depth.begin();

  std::vector<int> path_to_end;
  std::vector<char> on_path_to_end(n);
  for (int v = end; v != -1; v = parent[v]) {
    on_path_to_end[v] = true;
    path_to_end.push_back(v);
  }
  std::reverse(path_to_end.begin(), path_to_end.end());

  if ((int) path_to_end.size() >= k) {
    while ((int) path_to_end.size() > k) {
      path_to_end.pop_back();
    }
    print_answer(path_to_end);
    return;
  }

  std::vector<int> leaves;
  for (int i = 0; i < n; i++) {
    if (children[i].empty() && !on_path_to_end[i]) {
      leaves.push_back(i);
    }
  }

  int tree_size = n;
  while (tree_size > k) {
    assert(!leaves.empty());
    int leaf = leaves.back();
    assert(!on_path_to_end[leaf]);
    leaves.pop_back();

    int p = parent[leaf];
    auto res = children[p].erase(leaf);
    assert(res);
    tree_size--;

    if (children[p].empty() && !on_path_to_end[p]) {
      leaves.push_back(p);
    }
  }

  std::vector<int> path;

  std::function<void(int)> dfs = [&](int v) {
    path.push_back(v);
    std::vector<int> chs(children[v].begin(), children[v].end());
    std::partition(chs.begin(), chs.end(), [&](int ch) {
      return !on_path_to_end[ch];
    });
    for (int ch : chs) {
      dfs(ch);
      path.push_back(v);
    }
  };

  dfs(0);

  for (int v : path_to_end) {
    assert(!path.empty());
    assert(path.back() == v);
    if (v != end) {
      path.pop_back();
    }
  }

  std::set<int> path_as_set(path.begin(), path.end());
  assert((int) path_as_set.size() == k);

  print_answer(path);
}

int main() {
  int t;
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    solve();
  }
}
