/**
 *    author:  tourist
 *    created: 19.10.2018 15:52:38       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t, p;
  cin >> t >> p;
  if (p < 20) {
    p -= 20 - p;
  }
  cout << t * (p + 20.0) / (100.0 - p) << '\n';
  return 0;
}
