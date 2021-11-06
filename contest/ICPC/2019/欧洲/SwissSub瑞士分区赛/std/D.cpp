#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> v;
  copy_n(istream_iterator<int>(cin), n, back_inserter(v));
  bool ok = false;
  for (int i=0; i<n; ++i) {
    auto w = v; // make a copy
    rotate(w.begin(), w.begin()+i, w.end());
    ok |= is_sorted(w.begin(), w.end());
  }
  cout << (ok ? "Phew\n" : "Lie\n");
}