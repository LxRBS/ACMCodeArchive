/**
 *    author:  tourist
 *    created: 19.10.2018 16:03:38       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int len = (int) s.size();
  int n;
  cin >> n;
  vector<vector<int>> dp(2 * len, vector<int>(2 * len));
  for (int i = 0; i < 2 * len; i++) {
    for (int j = 0; j < 2 * len; j++) {
      if (s[i % len] == s[j % len]) {
        dp[i][j] = 1 + (i > 0 && j > 0 ? dp[i - 1][j - 1] : 0);
      } else {
        dp[i][j] = 0;
      }
    }
  }
  vector<int> adds(2 * len);
  for (int i = 0; i < 2 * len; i++) {
    int mx = 0;
    for (int j = 0; j < i; j++) {
      mx = max(mx, dp[i][j]);
    }
    adds[i] = (i + 1) - mx;
  }
  long long ans = 0;
  int ptr = 0;
  for (int i = 0; i < n; i++) {
    ans += adds[ptr];
    ptr++;
    if (ptr == 2 * len) {
      ptr -= len;
    }
  }
  cout << ans << '\n';
  return 0;
}
