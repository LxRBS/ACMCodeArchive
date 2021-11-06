/**
 *    author:  tourist
 *    created: 19.10.2018 18:19:20       
**/
#include <bits/stdc++.h>

using namespace std;

const int md = 998244353;

inline void add(int &a, int b) {
  a += b;
  if (a >= md) {
    a -= md;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  const int MAX = 200010;
  const int PARTS = 456;
  vector<vector<int>> dp(MAX, vector<int>(PARTS, 0));
  dp[0][0] = 1;
  for (int i = 0; i < MAX; i++) { 
    for (int j = 1; j < PARTS; j++) {
      dp[i][j] = dp[i][j - 1];
      if (i >= j) {
        add(dp[i][j], dp[i - j][j]);
      }
    }
  }
  vector<int> ans(MAX);
  for (int i = 1; i < MAX; i++) {
    ans[i] = 0;
    for (int k = 1; k * k <= i; k++) {
      int rm = i - k * k;
      if (rm % 2 == 0) {
        add(ans[i], dp[rm / 2][k]);
      }
    }
  }
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    cout << ans[n] << '\n';
  }
  return 0;
}
