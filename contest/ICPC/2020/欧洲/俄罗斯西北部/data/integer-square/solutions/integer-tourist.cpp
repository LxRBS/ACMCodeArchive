/**
 *    author:  tourist
 *    created: 09.11.2020 16:31:22       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int s;
  cin >> s;
  for (int x = 0; x * x <= s; x++) {
    for (int y = 0; y * y <= s; y++) {
      if (x * x + y * y == s) {
        cout << 0 << " " << 0 << '\n';
        cout << x << " " << y << '\n';
        cout << -y << " " << x << '\n';
        cout << x - y << " " << x + y << '\n';
        return 0;
      }
    }
  }
  cout << "Impossible" << '\n';
  return 0;
}
