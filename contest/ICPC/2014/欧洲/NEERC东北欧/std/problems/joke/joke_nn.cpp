/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem J. Jokewithpermutation                                 */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Maxim Babenko                            */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Niyaz Nigmatullin                        */
/******************************************************************/

#include <cassert>
#include <cstdio>

int s[1234];
int p[1234];
bool was[1234];
int cn;

int dig(int k) {
  return k < 10 ? 1 : 2;
}

int fitness = 0;

bool match(int num, int start, int n) {
  if (dig(num) == 1 && start < n) return s[start] == num;
  if (dig(num) == 2 && start + 1 < n) return s[start] * 10 + s[start + 1] == num;
  return false;
}

bool ok(int start, int maxn, int n) {
  for (int i = 1; i <= maxn; i++) {
    if (was[i]) continue;
    bool ok = false;
    for (int j = start; j < n; j++) {
      if (match(i, j, n)) {
        ok = true;
        break;
      }
    }
    if (!ok) return false;
  }
  return true;
}

int go(int x, int maxn, int n) {
  ++fitness;
  if (x == n) {
    return true;
  }
  cn++;
  for (int i = 1; i <= maxn; i++) {
    if (was[i] || !match(i, x, n)) continue;
    was[i] = true;
    p[cn - 1] = i;
    if (ok(x + dig(i), maxn, n)) {
      if (go(x + dig(i), maxn, n)) {
        return true;
      }
    }
    was[i] = false;
  }
  --cn;
  return false;
}

int main() {
  freopen("joke.in", "r", stdin);
  freopen("joke.out", "w", stdout);
  int n = 0;
  int c = getchar();
  while (c <= 32) c = getchar();
  while (c > 32) {
    s[n++] = c - '0';
    c = getchar();
  }
  int m = 0;
  int k = 0;
  while (m < n) {
    k++;
    m += dig(k);
  }
  cn = 0;
  if (go(0, k, n)) {
    for (int i = 0; i < k; i++) printf("%d ", p[i]);
    puts("");
  } else {
    puts("TOO BAD!!!");
  }
  fprintf(stderr, "fitness %d\n", fitness);
  return 0;
}

