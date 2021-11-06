/**
 *    author:  tourist
 *    created: 21.10.2018 03:07:33       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> x[2];
  for (int id = 0; id < 2; id++) {
    cout << "? " << n;
    for (int i = 1; i <= n; i++) {
      cout << " " << (id == 0 ? i : n - i + 1);
    }
    cout << endl;
    int foo;
    cin >> foo;
    x[id].resize(foo);
    for (int i = 0; i < foo; i++) {
      cin >> x[id][i];
    }
  }
  int m = (int) x[0].size();
  int skip = 0;
  cout << "!";
  for (int i = m - 1; i >= 0; i--) {
    if (x[1][i] == x[0][skip]) {
      cout << " " << m - skip - i;
      for (int j = i; j < m - skip; j++) {
        cout << " " << x[1][j];
      }
      skip = m - i;
    }
  }
  cout << endl;
  return 0;
}
