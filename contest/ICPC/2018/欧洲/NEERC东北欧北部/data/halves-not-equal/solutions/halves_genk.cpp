/**
 *    author:  tourist
 *    created: 19.10.2018 19:34:18       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int s;
  cin >> s;
  int sum = accumulate(a.begin(), a.end(), 0);
  int flag = 0;
  if (s > sum - s) {
    s = sum - s;
    flag = 1;
  }
  vector<double> b(n);
  double low = 0, high = 5000;
  for (int it = 0; it < 100; it++) {
    double mid = 0.5 * (low + high);
    for (int i = 0; i < n; i++) {
      b[i] = min(mid, 0.5 * a[i]);
    }
    if (it == 99) {
      break;
    }
    double sum_b = accumulate(b.begin(), b.end(), 0.0);
    if (sum_b > s) {
      high = mid;
    } else {
      low = mid;
    }
  }
  for (int i = 0; i < n; i++) {
    if (flag) {
      b[i] = a[i] - b[i];
    }
    cout << fixed << setprecision(17) << b[i] << '\n';
  }
  return 0;
}
