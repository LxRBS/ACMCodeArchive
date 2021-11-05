/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem I. Improvements                                        */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Niyaz Nigmatullin                        */
/******************************************************************/

#include <cstdio>
#include <algorithm>
 
using namespace std;

int const INF = 1 << 30;
int const N = 555555;

int id[N], a[N], dp[N];
int f[N], g[N];

bool bya(int i, int j) {
  return a[i] < a[j];
}

void solve(int n, int * f) {
  for (int i = 0; i <= n; i++) dp[i] = INF;
  dp[0] = -INF;
  int cn = 0;
  for (int i = 0; i < n; i++) {
    int x = id[i];
    int l = 0;
    int r = cn + 1;
    while (l < r - 1) {
      int mid = (l + r) >> 1;
      if (dp[mid] >= x) r = mid; else l = mid;
    }
    dp[l + 1] = x;
    if (l + 1 > cn) cn = l + 1;
    f[i] = l + 1;
  }
  for (int i = 1; i < n; i++) if (f[i] < f[i - 1]) f[i] = f[i - 1];
}

int main() {
  freopen("improvements.in", "r", stdin);
  freopen("improvements.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
    id[i] = i;
  }
  std::sort(id, id + n, bya);
  solve(n, f);
  std::reverse(id, id + n);
  solve(n, g);
  std::reverse(g, g + n);
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    int left = i > 0 ? f[i - 1] : 0;
    int right = i < n ? g[i] : 0;
    if (left + right > ans) ans = left + right;
  } 
  printf("%d\n", ans);
}

