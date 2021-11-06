#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

char s[2010];
int dp[2010][2010];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  int k;
  scanf("%d", &k);
  memcpy(s + n, s, n);

  for (int i = 0; i < 2 * n; i++) {
    for (int j = 0; j < 2 * n; j++) {
      if (s[i] == s[j]) {
        dp[i][j] = ((i && j) ? dp[i - 1][j - 1] : 0) + 1;
      } else {
        dp[i][j] = 0;
      }
    }
  }

  long long ans = 1;
  for (int i = 1; i < 2 * n && i < k; i++) {
    ans += i - *max_element(dp[i], dp[i] + i) + 1;
  }
  ans += max(0, k - 2 * n) * 1LL * n;
  printf("%lld\n", ans);
}
