#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> scores(n);
  vector<double> pw(m + 1);
  for (int i = 0; i < pw.size(); ++i) pw[i] = i < 5 ? 1.0 : 0.0;
  mt19937 rng(57);
  for (int step = 0; step < m; ++step) {
    int mn = scores[0];
    for (int x : scores) mn = min(mn, x);
    double w = 0;
    for (int x : scores) w += pw[x - mn];
    w *= uniform_real_distribution<double>(0, 1)(rng);
    int bi = -1;
    for (int i = 0; i < n; ++i) {
      w -= pw[scores[i] - mn];
      if (w < 0) {
        bi = i;
        break;
      }
    }
    string s;
    cin >> s;
    cout << s[bi] << endl;
    int a;
    cin >> a;
    for (int i = 0; i < n; ++i) if (s[i] != '0' + a) ++scores[i];
  }
  return 0;
}