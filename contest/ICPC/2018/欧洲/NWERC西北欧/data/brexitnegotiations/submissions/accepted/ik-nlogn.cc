#include <bits/stdc++.h>
using namespace std;

class CompareDist {
public:
    bool operator() (pair<int,int> n1, pair<int,int> n2) {
        return n1.first < n2.first;
    }
};

int main() {
  int n;

  cin >> n;

  int weights[n];
  map<int, set<int> > out_edges;
  map<int, set<int> > in_edges;
  multiset<pair<int,int>,CompareDist> sinks;

  for (int i = 0; i < n; i++) {
    int d;

    cin >> weights[i] >> d;

    for (int j = 0; j < d; j++) {
      int v;
      cin >> v;
      --v;
      in_edges[i].insert(v);
      out_edges[v].insert(i);
    }
  }

  for (int i = 0; i < n; i++) {
    if (out_edges.find(i) == out_edges.end())
      sinks.insert(make_pair(weights[i],i));
  }

  int total_length = 0;
  int pos = n-1;
  while (!sinks.empty()) {
    auto s = sinks.begin();
    total_length = total_length > s->first + pos ? total_length : s->first + pos;

    for (int v : in_edges[s->second]) {
      out_edges[v].erase(s->second);
      if (out_edges[v].empty())
        sinks.insert(make_pair(weights[v],v));
    }

    sinks.erase(s);
    pos--;
  }

  cout << total_length << endl;
}
