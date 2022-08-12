#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 500001;
const int P = 1'000'000'007;

typedef vector<int> vi;

inline int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
inline int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
inline int mul(int a, int b) { return 1ll * a * b % P; }
inline int qpm(int a, int b) {
    int r = 1;
    do if (b & 1) r = mul(r, a);
    while (a = mul(a, a), b >>= 1);
    return r;
}
inline int inv(int x) { return qpm(x, P - 2); }

int invs[N], fac[N], ifac[N];
int binom(int n, int k) { return mul(fac[n], mul(ifac[n - k], ifac[k])); }
void ginv() {
    invs[1] = 1; fac[0] = ifac[0] = 1;
    for (int i = 2; i != N; ++i) invs[i] = mul(invs[P % i], (P - P / i));
    for (int i = 1; i != N; ++i) fac[i] = mul(fac[i - 1], i);
    for (int i = 1; i != N; ++i) ifac[i] = mul(ifac[i - 1], invs[i]);
}

int lintp(const vector<int>& x, const vector<int>& y, int k) {
    int ans = 0;
	for (int i = 0; i != x.size(); ++i) {
        if (k == x[i])
            return y[i];
		int u = 1, v = 1;
		for (int j = 0; j != x.size(); ++j) {
			if (i == j) continue;
			u = mul(u, sub(k, x[j]));
			v = mul(v, sub(x[i], x[j]));
		}
		ans = add(ans, mul(y[i], mul(u, inv(v))));
    }
    return ans;
}

namespace min25 {

const int N = 1000005;
bool ip[N]; vector<int> ps;
void sieve() {
    fill_n(ip, N, 1); ip[1] = 0;
    for (int i = 2; i < N; ++i) {
        if (ip[i]) ps.push_back(i);
        for (int j : ps) {
            if (i * j >= N) break;
            ip[i * j] = 0;
            if (i % j == 0) break;
        }
    }
}

ll n, sq, w[N]; int c;
ll g[N];

inline int id(ll x) { return x ? x <= sq ? c - x + 1 : n / x : 0; }

void cal_g(ll n_) {
    n = n_; sq = sqrt(n_); c = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        ll v = w[++c] = n / l; r = n / v;
        g[c] = (v - 1) % P;
    }
    for (int p : ps) {
        if (1ll * p * p > n) break;
        for (int j = 1; 1ll * p * p <= w[j]; ++j)
            g[j] -= g[id(w[j] / p)] - g[id(p - 1)];
    }
}

int cal_s(int n, int i, ll x) {
    int p = ps[i];
    if (x < p) return 0;
    int sum = 0;
    if (1ll * p * p > x)
        sum = mul(n, sub(g[id(x)], i == 0 ? 0 : g[id(ps[i - 1])]));
    else {
        sum = cal_s(n, i + 1, x);
        ll q = p;
        for (int e = 1; q <= x; e++, q *= p)
            sum = add(sum, mul(binom(n + e - 1, n - 1), add(cal_s(n, i + 1, x / q), 1)));
    }
    return sum;
}

int cal_sf(ll n, ll m) {
    cal_g(m);
    vector<int> x, y;
    for (int i = 1; i <= 32; ++i) {
        x.push_back(i);
        y.push_back(add(y.empty() ? 0 : y.back(), add(cal_s(i, 0, m), 1)));
    }
    return lintp(x, y, n);
}

}


int main(void) {
    ginv();
    min25::sieve();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        printf("%d\n", min25::cal_sf(n, m));
    }
    
    return 0;
}