#include <bits/stdc++.h>

using namespace std;

int BUBEN = 5;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> scores(n);
  mt19937 rng(57);
  uniform_int_distribution<int> distrib(0, n - 1);
  int now = distrib(rng);
  for (int step = 0; step < m; ++step) {
    string s;
    cin >> s;
    int mn = scores[0];
    for (int x : scores) mn = min(mn, x);
    while (scores[now] > mn + BUBEN) {
      now = distrib(rng);
    }
    cout << s[now] << endl;
    int a;
    cin >> a;
    for (int i = 0; i < n; ++i) if (s[i] != '0' + a) ++scores[i];
  }
  return 0;
}