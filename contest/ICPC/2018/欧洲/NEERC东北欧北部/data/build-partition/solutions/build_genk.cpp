/**
 *    author:  tourist
 *    created: 19.10.2018 18:18:00       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  if (n == 2) {
    cout << "-1" << '\n';
    return 0;
  }
  vector<string> s(n, string(n, '.'));
  for (int i = 0; i <= (n - 1) / 2; i++) {
    s[i][0] = s[0][i] = 'o';
  }
  if (n % 2 == 0) {
    s[1][1] = 'o';
  }
  cout << n << '\n';
  for (int i = n - 1; i >= 0; i--) {
    cout << s[i] << '\n';
  }
  return 0;
}
