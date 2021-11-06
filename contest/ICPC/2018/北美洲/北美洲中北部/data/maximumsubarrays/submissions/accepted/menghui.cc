#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;

static const ll INF = 0xffffffffll * 100000ll;

int main() {
  int n, k;
  cin >> n >> k;
  vl a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  vvvl dp(2, vvl(n, vl(2, 0)));
  for (int kk = 1; kk <= k; ++kk) {
    int index = kk % 2;
    dp[index][0][0] = dp[index][0][1] = kk == 1 ? a[0] : -INF;
    for (int i = 1; i < n; ++i) {
      dp[index][i][1] =
          a[i] + std::max(dp[1 - index][i - 1][0], dp[index][i - 1][1]);
      dp[index][i][0] = std::max(dp[index][i][1], dp[index][i - 1][0]);
    }
  }
  cout << dp[k % 2][n - 1][0] << endl;
  return 0;
}
