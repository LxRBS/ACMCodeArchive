/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem A. Alter Board                                         */
/*                                                                */
/* Original idea         Egor Kulikov                             */
/* Problem statement     Egor Kulikov                             */
/* Test set              Egor Kulikov                             */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Evgeny Kurpilyanskiy                     */
/******************************************************************/

#include <cstdio>

int main() {
  freopen("alter.in", "r", stdin);
  freopen("alter.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  printf("%d\n", n / 2 + m / 2);
  for (int x = 2; x <= n; x += 2) {
    printf("%d %d %d %d\n", x, 1, x, m);
  }
  for (int y = 2; y <= m; y += 2) {
    printf("%d %d %d %d\n", 1, y, n, y);
  }
  return 0;
}
