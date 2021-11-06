/**
 *    author:  tourist
 *    created: 13.11.2020 15:29:58       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  double p;
  cin >> n >> p;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<int> d(n - 1);
  for (int i = 0; i < n - 1; i++) {
    d[i] = a[i + 1] - a[i];
  }
  int pos = 0;
  int neg = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n - 1; j++) {
      int len = j - i + 1;
      double avg = (double) (a[j + 1] - a[i]) / len;
      double dev = 0;
      for (int k = i; k <= j; k++) {
        dev += (avg - d[k]) * (avg - d[k]);
      }
      dev = sqrt(dev / len);
      if (avg > dev * p) {
        pos += 1;
      }
      if (avg < -dev * p) {
        neg += 1;
      }
    }
  }
  cout << pos << " " << neg << '\n';
  return 0;
}
