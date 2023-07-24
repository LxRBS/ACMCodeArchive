#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll P = 998244353;
const ll G = 3;

inline ll pw(ll a, ll x = P - 2) {
    ll ret = 1;
    for (; x; x >>= 1, a = a * a % P) if (x & 1) ret = ret * a % P;
    return ret;
}

typedef vector<ll> Poly;

struct Polynome {
    ll m;
    vector<ll> w, inv, lim;

    void DFT(Poly &a) {
        a.resize(m, 0);
        for (int k = m >> 1; k; k >>= 1) {
            for (int i = 0; i < m; i += k << 1) {
                for (int j = 0; j < k; ++j) {
                    ll x = a[i + j] % P, y = a[i + j + k] % P;
                    a[i + j + k] = (x + P - y) * w[j + k], a[i + j] = x + y;
                }
            }
        }
        for (auto &x: a) x %= P;
    }

    void IDFT(Poly &a) {
        a.resize(m, 0);
        for (int k = 1; k < m; k <<= 1) {
            for (int i = 0; i < m; i += k << 1) {
                for (int j = 0; j < k; ++j) {
                    ll x = a[i + j] % P, y = a[i + j + k] * w[j + k] % P;
                    a[i + j + k] = x + P - y, a[i + j] = x + y;
                }
            }
        }
        ll iv = P - P / m;
        for (auto &x: a) x = x * iv % P;
        reverse(a.begin() + 1, a.end());
    }

public:
    Polynome(int maxL = 23) {
        int n = 1 << maxL;
        w.resize(n), lim.resize(n), inv.resize(n);
        lim[0] = inv[1] = 1;
        for (ll i = n >> 1, x = pw(G, P / n); i; i >>= 1, x = x * x % P) {
            w[i] = 1;
            for (int j = i + 1; j < i * 2; ++j) w[j] = w[j - 1] * x % P;
        }
        for (int i = 1; i < n; ++i) lim[i] = lim[i >> 1] << 1;
        for (int i = 2; i < n; ++i) inv[i] = (P - P / i) * inv[P % i] % P;
    }

    Poly Inv(const Poly &a) {
        Poly d(1, pw(a[0]));
        function<void(int)> mInv = [&](int len) {
            if (len > 2) mInv((len + 1) >> 1);
            Poly f(a.begin(), a.begin() + len);
            m = lim[len << 1], DFT(f), DFT(d);
            for (int i = 0; i < m; ++i) (d[i] *= P + 2 - f[i] * d[i] % P) %= P;
            IDFT(d), d.resize(len);
        };
        return mInv(a.size()), d;
    }

    Poly Sqrt(const Poly &a) {
        Poly d(1, 1);
        function<void(int)> mSqrt = [&](int len) {
            if (len > 2) mSqrt((len + 1) >> 1);
            d.resize(len);
            Poly f(a.begin(), a.begin() + len), g = Inv(d);
            m = lim[len << 1], DFT(f), DFT(d), DFT(g);
            for (int i = 0; i < m; ++i) {
                d[i] = (d[i] + f[i] * g[i]) % P;
                d[i] = (d[i] + (d[i] & 1 ? P : 0)) >> 1;
            }
            IDFT(d), d.resize(len);
        };
        return mSqrt(a.size()), d;
    }
};

Polynome pol(18);

// [2,k+1]部分
vector<ll> init(int n, int k) {
    vector<ll> g(n);
    g[0] = 1, g[1] = -2, g[2] = -3;
    g = pol.Sqrt(g);
    (g[0] += 1) %= P;
    (g[1] += P - 1) %= P;
    const ll inv2 = (P + 1) / 2;
    for (int i = 0; i < n; ++i) (g[i] *= inv2) %= P;
    for (int i = k + 1; i < n; ++i) g[i] = 0;
    return pol.Inv(g);
}

int main() {
    int n, K;
    cin >> n >> K;
    auto f = init(n + 10, K + 1);
    vector<vector<int>> G(n + 1);
    for (int u = 1; u <= n; ++u) {
        int x, y;
        cin >> x >> y;
        if (x) G[u].push_back(x);
        if (y) G[u].push_back(y);
    }

    ll ans = 1;
    // 此处使用半在线卷积求逆，可以直接使用inv带公式
    function<void(int, int, int)> dfs = [&](int u, int r, int len) {
        if (G[u].size() == 2) {
            dfs(G[u][0], 1, 0);
            dfs(G[u][1], 0, 0);
            if (!r) (ans *= len < K ? 0 : f[len - K]) %= P;
            else (ans *= f[len]) %= P;
        } else if (G[u].size() == 1) {
            dfs(G[u][0], r, len + 1);
        } else {
            if (!r) (ans *= f[len]) %= P;
            else (ans *= f[len + K]) %= P;
        }
    };

    dfs(1, 0, 0);
    cout << ans << endl;
    return 0;
}
