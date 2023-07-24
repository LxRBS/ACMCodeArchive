#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

const ll inf = 1e18;

void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
    if (!b) d = a, x = 1, y = 0;
    else exgcd(b, a % b, d, y, x), y -= x * (a / b);
}

pll excrt(pll l, pll r) {
    auto[r1, m1] = l;
    auto[r2, m2] = r;
    if (r1 == -1 || r2 == -1) return {-1, -1};
    ll d, l1, l2;
    exgcd(m1, m2, d, l1, l2);
    if ((r2 - r1) % d) return {-1, -1};
    ll L = m1 * m2 / d;
    ll R = ((r1 + (r2 - r1) / d * l1 % L * m1) % L + L) % L;
    return {R, L};
}

int main() {
    ll n;
    cin >> n;
    vector<ll> a(n + 1), b(n + 1), c(n + 1);
    vector<ll> ia(n + 1), ib(n + 1), ic(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i], ia[a[i]] = i;
    for (int i = 1; i <= n; ++i) cin >> b[i], ib[b[i]] = i;
    for (int i = 1; i <= n; ++i) cin >> c[i], ic[c[i]] = i;

    // 计算三个置换
    vector<ll> abc(n + 1), bca(n + 1), cab(n + 1);
    for (int i = 1; i <= n; ++i) abc[i] = a[b[c[i]]];
    for (int i = 1; i <= n; ++i) bca[i] = b[c[a[i]]];
    for (int i = 1; i <= n; ++i) cab[i] = c[a[b[i]]];
    ll lena = 0, lenb = 0, lenc = 0;
    // 计算到每个点的时间距离+周期
    vector<ll> disa(n + 1, -1), disb(n + 1, -1), disc(n + 1, -1);
    for (ll u = 1; disa[u] == -1; u = abc[u], ++lena) disa[u] = lena;
    for (ll u = 1; disb[u] == -1; u = bca[u], ++lenb) disb[u] = lenb;
    for (ll u = 1; disc[u] == -1; u = cab[u], ++lenc) disc[u] = lenc;

    // EXCRT
    auto solve = [&](ll x, ll y, ll z) -> ll {
        if (disa[x] == -1 || disb[y] == -1 || disc[z] == -1) return inf;
        pll A(disa[x], lena);
        pll B(disb[y], lenb);
        pll C(disc[z], lenc);
        A = excrt(A, excrt(B, C));
        return A.first == -1 ? inf : A.first;
    };

    int T;
    cin >> T;
    while (T--) {
        ll x, y, z;
        cin >> x >> y >> z;
        ll m0 = solve(x, y, z);
        ll m1 = solve(ic[z], ia[x], ib[y]);
        ll m2 = solve(ic[ib[y]], ia[ic[z]], ib[ia[x]]);
        ll ans = min({m0 * 3, m1 * 3 + 1, m2 * 3 + 2});
        printf("%lld\n", ans >= inf ? -1 : ans);
    }
    return 0;
}
