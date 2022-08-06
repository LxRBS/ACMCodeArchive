#include <bits/stdc++.h>
using namespace std;

const int N = 1<<18;
const int P = 998244353;

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


namespace NTT1 {

using ::mul;
using ::inv;

const int W = 18, S = 1 << W, g = 3;
int w[S + 1], rev[S << 1], *r[W + 1];
void init() {
    for (int s = 0; s <= W&&(r[s]=rev+(1<<s),1); ++s)
        for (int i = 0; i != (1 << s); ++i)
            r[s][i] = (r[s][i >> 1] >> 1) | ((i & 1) << (s - 1));
    w[0] = 1; w[1] = qpm(g, (P - 1) / S);
    for (int i = 2; i <= S; ++i) w[i] = mul(w[i - 1], w[1]);
}

int m, s, im;
int init(int n) {
    for (s = 0, m = 1; m < n; m <<= 1, ++s);
    im = inv(m); return m;
}

void ntt(int* p, const int t) {
    for (int i = 0; i != m; ++i) if (i < r[s][i]) swap(p[i], p[r[s][i]]);
    for (int i = 1, z = 0; i != m; i <<= 1, z++)
        for (int j = 0; j != m; j += (i << 1))
            for (int k = 0, u, v; k != i; k++)
                u = p[j+k], v = mul(w[(t?(i<<1)-k:k)<<W-z-1], p[i+j+k]),
                p[j + k] = add(u, v), p[i + j + k] = sub(u, v);
    if (t) for (int i = 0; i != m; ++i) p[i] = mul(p[i], im);
}

int px[S], py[S];
vi pmul(const vi& p1, const vi& p2, int n = 0) {
    int n1 = p1.size(), n2 = p2.size(), n3 = n1 + n2 - 1;
    init(n3);
    copy_n(p1.begin(), n1, px); fill(px + n1, px + m, 0);
    copy_n(p2.begin(), n2, py); fill(py + n2, py + m, 0);
    ntt(px, 0); ntt(py, 0);
    for (int i = 0; i != m; ++i) px[i] = mul(px[i], py[i]);
    ntt(px, 1); vi p3(n3); copy_n(px, n3, p3.begin());
    if (n && n3 > n) p3.resize(n); return p3;
}

vi pinv(const vi& p1) {
    int n1 = p1.size(), n2 = (n1 + 1) >> 1;
    if (n1 == 1) return { inv(p1[0]) };
    else {
        vi p2 = pinv(vi(p1.begin(), p1.begin() + n2));
        init(n1 << 1);
        copy_n(p1.begin(), n1, px); fill(px + n1, px + m, 0);
        copy_n(p2.begin(), n2, py); fill(py + n2, py + m, 0);
        ntt(px, 0); ntt(py, 0);
        for (int i = 0; i != m; ++i)
            px[i] = mul(sub(2, mul(px[i], py[i])), py[i]);
        ntt(px, 1); vi p3(n1); copy_n(px, n1, p3.begin());
        return p3;
    }
}

}

using NTT1::init;
using NTT1::pmul;
using NTT1::pinv;

vi padd(const vi& p1, const vi& p2) {
    int n3 = max(p1.size(), p2.size());
    vi pr = p1; pr.resize(n3, 0);
    for (int i = 0; i != p2.size(); ++i) pr[i] = add(pr[i], p2[i]);
    return pr;
}

vi psub(const vi& p1, const vi& p2) {
    int n3 = max(p1.size(), p2.size());
    vi pr = p1; pr.resize(n3, 0);
    for (int i = 0; i != p2.size(); ++i) pr[i] = sub(pr[i], p2[i]);
    return pr;
}

const int M = 10000001;

int invs[M], fac[M], ifac[M];
int binom(int n, int k) { return mul(fac[n], mul(ifac[n - k], ifac[k])); }
void ginv() {
    invs[1] = 1; fac[0] = ifac[0] = 1;
    for (int i = 2; i != M; ++i) invs[i] = mul(invs[P % i], (P - P / i));
    for (int i = 1; i != M; ++i) fac[i] = mul(fac[i - 1], i);
    for (int i = 1; i != M; ++i) ifac[i] = mul(ifac[i - 1], invs[i]);
}

int main(void) {
    ginv();
    init();

    int w; scanf("%d", &w);
    vector<int> c(w);
    for (int& e : c) scanf("%d", &e);

    int s = 0;
    for (int e : c) s += e;

    vector<vi> g(1, vi(1, 1));
    for (int e : c) {
        vi f(ifac, ifac + e);
        
        vector<vi> tmp;
        tmp.push_back(vi(1, 0));
        for (int i = 0; i < (int)g.size(); ++i) {
            tmp[i] = psub(tmp[i], pmul(g[i], f));
            tmp.push_back(move(g[i]));
        }
        g = move(tmp);
    }

    int q; scanf("%d", &q);
    while (q--) {
        int n; scanf("%d", &n);
        int ans = 0;
        for (int i = 0; i <= w; ++i) {
            int u = min(n, (int)g[i].size() - 1);
            int z = qpm(i, n - u);
            for (int j = u; j >= 0; --j) {
                ans = add(ans, mul(mul(z, ifac[n - j]), g[i][j]));
                z = mul(z, i);
            }
        }
        printf("%d\n", mul(ans, fac[n]));
    }

    return 0;
}