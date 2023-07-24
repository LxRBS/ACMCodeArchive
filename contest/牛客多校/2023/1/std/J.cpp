#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll P = 998244353;

inline ll pw(ll a, ll x = P - 2) {
    ll ret = 1;
    for (; x; x >>= 1, a = a * a % P) if (x & 1) ret = ret * a % P;
    return ret;
}

int main() {
    ll n, m, ans = 1;
    cin >> n >> m, m += n;
    while (n < m) {
        ll i = __lg(n + 1);
        ll r = min(m, (1ll << (i + 1)) - 1);
        (ans *= pw(P + 1 - pw(2, P - 1 - i), r - n)) %= P;
        n = r;
    }
    cout << ans << endl;
    return 0;
}
