#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
  int T, encrypted_data, P, Q;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &P, &Q, &encrypted_data);
    ll kM = 1ll * P * Q - 1, raw_data = -1, M;
    for (ll i = 2; i * i <= kM; ++i) {
      if (kM % i) continue;
      while (kM % i == 0) kM /= i;
      M = i;
    }
    if (kM > 1) M = kM;
    if (P < M && Q < M) raw_data = 1ll * encrypted_data * Q % M;
    if (~raw_data) printf("%lld\n", raw_data);
    else puts("shuanQ");
  }
}