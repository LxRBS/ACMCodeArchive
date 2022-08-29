//1013, std O(nlogn)
#include<bits/stdc++.h>
#define mset(a, b) memset(a, b, sizeof(a))
#define mcpy(a, b) memcpy(a, b, sizeof(a))
using namespace std;
typedef long long LL;
const int MAXN = (1 << 19) + 5;

template <typename T> inline void read(T &WOW) {
    T x = 0, flag = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') flag = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    WOW = flag * x;
}

namespace ModCalculator {
    const int MOD = 998244353;
    inline void Inc(int &x, int y) {
        x += y; if (x >= MOD) x -= MOD;
    }
    inline int Add(int x, int y) {
        Inc(x, y); return x;
    }
    inline void Dec(int &x, int y) {
        x -= y; if (x < 0) x += MOD;
    }
    inline int Sub(int x, int y) {
        Dec(x, y); return x;
    }
    inline int Mul(int x, int y) {
        return 1LL * x * y % MOD;
    }
    inline int Ksm(int x, int y) {
        int ret = 1;
        for (; y; y >>= 1) {
            if (y & 1) ret = Mul(ret, x);
            x = Mul(x, x);
        }
        return ret;
    }
    inline int Inv(int x) {
        return Ksm(x, MOD - 2);
    }
}
using namespace ModCalculator;

int n, m, fac[MAXN], pw[MAXN];
int len, rev[MAXN], w1[MAXN], w2[MAXN], A[MAXN], B[MAXN], C[MAXN];

void prework() {
    n = 400000;
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = Mul(fac[i - 1], i);
    }
    for (len = 1; len < n; len <<= 1);
    int Gi = 3, Gv = Inv(Gi);
    for (int i = 1; i < len; i <<= 1) {
        int wk1 = Ksm(Gi, MOD / (i << 1)), wnk1 = 1;
        int wk2 = Ksm(Gv, MOD / (i << 1)), wnk2 = 1;
        for (int k = 0; k < i; ++k) {
            w1[i + k] = wnk1;
            wnk1 = Mul(wnk1, wk1);
            w2[i + k] = wnk2;
            wnk2 = Mul(wnk2, wk2);
        }
    }
}

void GetRev(int _n) {
    int bit = -1;
    for (len = 1; len < _n; len <<= 1) ++bit;
    for (int i = 0; i < len; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << bit);
    }
}

void NTT(int *a, int type) {
    int *w = (type == 1? w1 : w2);
    for (int i = 0; i < len; ++i) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int i = 1; i < len; i <<= 1) {
        for (int j = 0; j < len; j += (i << 1)) {
            for (int k = 0; k < i; ++k) {
                int x = a[j + k], y = Mul(w[i + k], a[j + k + i]);
                a[j + k] = Add(x, y);
                a[j + k + i] = Sub(x, y);
            }
        }
    }
    if (type == 1) return;
    int lenv = Inv(len);
    for (int i = 0; i < len; ++i) {
        a[i] = Mul(a[i], lenv);
    }
}

void Poly_Inv(int n, int *a, int *b) {
    if (n == 1) {
        b[0] = Inv(a[0]);
        return;
    }
    Poly_Inv((n + 1) >> 1, a, b);
    GetRev(n << 1);
    copy(a, a + n, C);
    fill(C + n, C + len, 0);
    NTT(b, 1); NTT(C, 1);
    for (int i = 0; i < len; ++i) {
        b[i] = Mul(Sub(2, Mul(b[i], C[i])), b[i]);
    }
    NTT(b, -1);
    fill(b + n, b + len, 0);
}

void solve() {
    read(n); read(m);
    pw[0] = 1;
    for (int i = 1; i <= m; ++i) {
        pw[i] = Mul(pw[i - 1], n);
    }

    mset(A, 0);
    mset(B, 0);
    A[0] = 1;
    for (int i = 0; i + n <= m - n + 1; ++i) {
        Inc(A[i + n], Mul(pw[i], fac[n]));
    }
    for (int i = 1; i <= n - 1 && i <= m - n + 1; ++i) {
        Inc(A[i], fac[i]);
    }
    Poly_Inv(m - n + 2, A, B);

    for (int i = 0; i <= m - n + 1; ++i) {
        A[i] = Mul(pw[i], fac[n]);
    }
    GetRev((m - n + 2) << 1);
    NTT(A, 1); NTT(B, 1);
    for (int i = 0; i < len; ++i) {
        A[i] = Mul(A[i], B[i]);
    }
    NTT(A, -1);

    int ans = pw[m];
    for (int i = 1; i <= m - n + 1; ++i) {
        Dec(ans, Mul(A[i - 1], pw[m - i - n + 1]));
    }
    printf("%d\n", ans);
}

int main() {
    prework();
    int T; read(T);
    while (T--) {
        solve();
    }
    return 0;
}
