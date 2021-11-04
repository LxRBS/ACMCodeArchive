#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; ++qq) {
    string s;
    cin >> s;
    vector<int> w(26);
    for (char c : s) {
      ++w[c - 'a'];
    }
    cout << "Case #" << qq << ": " << *max_element(w.begin(), w.end()) << "\n";
  }
  return 0;
}