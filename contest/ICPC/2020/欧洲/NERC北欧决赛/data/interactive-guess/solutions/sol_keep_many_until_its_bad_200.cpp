#include <bits/stdc++.h>

using namespace std;

int BUBEN = 200;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> scores(n);
  mt19937 rng(57);
  set<int> candidates;
  auto reset = [&]() {
    int mn = scores[0];
    for (int x : scores) mn = min(mn, x);
    for (int i = 0; i < n; ++i) if (scores[i] <= mn + BUBEN) {
      candidates.insert(i);
    }
  };
  for (int step = 0; step < m; ++step) {
    string s;
    cin >> s;
    int mn = scores[0];
    for (int x : scores) mn = min(mn, x);
    vector<int> cur(candidates.begin(), candidates.end());
    for (int x : cur) {
      if (scores[x] > mn + BUBEN) candidates.erase(x);
    }
    if (candidates.empty()) {
      reset();
    }
    assert(!candidates.empty());
    int n0 = 0;
    int n1 = 0;
    for (int x : candidates) {
      if (s[x] == '0') ++n0; else ++n1;
    }
    if (uniform_int_distribution<int>(0, n0 + n1 - 1)(rng) < n0)
      cout << 0 << endl;
    else
      cout << 1 << endl;
    int a;
    cin >> a;
    for (int i = 0; i < n; ++i) if (s[i] != '0' + a) ++scores[i];
  }
  return 0;
}