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
  vector<int> dp(MAX >> 1, 0);
  vector<int> ans(MAX, 0);
  dp[0] = 1;
  for (int j = 1; j * j < MAX; j++) {
    int sq = j * j;
    int bound = (MAX - 1 - sq) >> 1;
    for (int i = j; i <= bound; i++) { 
      add(dp[i], dp[i - j]);
    }
    for (int k = 0; k <= bound; k++) {
      add(ans[sq + (k << 1)], dp[k]);
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
