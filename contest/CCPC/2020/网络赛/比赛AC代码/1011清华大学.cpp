#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> a[i][j];
      }
    }
    vector<vector<int>> b(3, vector<int>(3));
    bool bad = false;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        cin >> b[i][j];
        if ((i || j) && b[i][j]) {
          bad = true;
        }
      }
    }
    if (bad) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (j) {
            cout << " ";
          }
          cout << 0;
        }
        cout << "\n";
      }
    } else {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (j) {
            cout << " ";
          }
          cout << a[i][j];
        }
        cout << "\n";
      }
    }
  }
  return 0;
}