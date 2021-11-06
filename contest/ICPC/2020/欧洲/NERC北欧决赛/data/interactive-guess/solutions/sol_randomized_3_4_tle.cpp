#include <bits/stdc++.h>

using namespace std;

double vbeta = 3.0 / 4;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> scores(n);
  vector<double> pw(m + 1);
  pw[0] = 1;
  for (int i = 1; i < pw.size(); ++i) pw[i] = vbeta * pw[i - 1];
  mt19937 rng(57);
  for (int step = 0; step < m; ++step) {
    int mn = scores[0];
    for (int x : scores) mn = min(mn, x);
    double w = 0;
    for (int x : scores) w += pw[x - mn];
    w *= uniform_real_distribution<double>(0, 1)(rng);
    int bi = -1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 1000; ++j) {
        w -= pw[scores[i] - mn] * 0.001;
      }
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