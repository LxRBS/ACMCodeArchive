#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> scores(n);
  vector<double> pw(m + 1);
  for (int i = 0; i < pw.size(); ++i) pw[i] = i < 2 ? 1.0 : 0.0;
  mt19937 rng(57);
  for (int step = 0; step < m; ++step) {
    string s;
    cin >> s;
    int mn = scores[0];
    for (int x : scores) mn = min(mn, x);
    double w0 = 0;
    double w1 = 0;
    for (int i = 0; i < n; ++i) {
      double cw = pw[scores[i] - mn];
      if (s[i] == '0') w0 += cw; else w1 += cw;
    }
    cout << (w0 >= w1 ? '0' : '1') << endl;
    int a;
    cin >> a;
    for (int i = 0; i < n; ++i) if (s[i] != '0' + a) ++scores[i];
  }
  return 0;
}