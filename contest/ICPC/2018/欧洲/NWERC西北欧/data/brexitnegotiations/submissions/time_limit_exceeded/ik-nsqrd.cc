#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;

  cin >> n;

  map<int, int> nodes;
  map<int, set<int> > out_edges;
  map<int, set<int> > in_edges;

  for (int i = 0; i < n; i++) {
    int d;

    cin >> nodes[i] >> d;

    for (int j = 0; j < d; j++) {
      int v;
      cin >> v;
      --v;
      in_edges[i].insert(v);
      out_edges[v].insert(i);
    }
  }


  int total_length = 0;
  for (int i = 0; i < n; i++) {
    int min_v;
    int min_w = 1000000;

    for (auto node : nodes) {
      if (out_edges[node.first].empty() && min_w > node.second) {
        min_v = node.first;
        min_w = node.second;
      }
    }

    total_length = total_length > min_w + n-1-i ? total_length : min_w + n-1-i;

    for (int v : in_edges[min_v]) {
      out_edges[v].erase(min_v);
    }
    nodes.erase(min_v);
  }

  cout << total_length << endl;
}
