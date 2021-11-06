/**
 *    author:  tourist
 *    created: 19.10.2018 16:15:27       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  map<string,int> mx;
  for (int i = 0; i < k; i++) {
    string s;
    cin >> s;
    int id = 1;
    while (s == "Re:") {
      id++;
      cin >> s;
    }
    mx[s] = max(mx[s], id);
  }
  int ans = 0;
  for (auto &p : mx) {
    ans = max(ans, p.second);
    n -= p.second;
  }
  if (n < 0) {
    cout << "NO" << '\n';
    return 0;
  }
  cout << "YES" << '\n';
  return 0;
}
