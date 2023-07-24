#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll inf = 1e18;

void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
    if (!b) d = a, x = 1, y = 0;
    else exgcd(b, a % b, d, y, x), y -= x * (a / b);
}

ll wk() {
    ll a, b, c, g, x, y;
    cin >> a >> b >> c;
    exgcd(a, b, g, x, y);
    if (c % g) return -1;
    a /= g, b /= g, c /= g, x *= c, y *= c;

    ll ans = inf;
    // 求次数
    auto wk = [&](ll t) {
        ll r = x + b * t, s = y - a * t;
        if (r >= 0 && s >= 0) ans = min(ans, 2 * (r + s));
        else ans = min(ans, 2 * (abs(r) + abs(s)) - 1);
    };
    
    // 附近找最小值
    ll t0 = -x / b;
    for (ll t = t0 - 1; t <= t0 + 1; ++t) wk(t);
    t0 = y / a;
    for (ll t = t0 - 1; t <= t0 + 1; ++t) wk(t);
    return ans;
}

int main() {
    int T;
    cin >> T;
    while (T--) cout << wk() << endl;
    return 0;
}

