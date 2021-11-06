#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace mod {
    typedef long long ll;
    const int MOD = 998244353;

    void add(int &a, ll b) {
        a = (a + b) % MOD;
    }

    int mul(int a, int b) {
        return 1LL * a * b % MOD;
    }

    int bin(int a, ll n) {
        int res = 1;
        while (n) {
            if (n & 1) res = 1LL * res * a % MOD;
            a = 1LL * a * a % MOD;
            n >>= 1;
        }
        return res;
    }

    int inv(int x) {
        return bin(x, MOD - 2);
    }
}
using namespace mod;

namespace fft {
    std::vector<int> root;
    std::vector<int> rev;
    int N;

    void prepRoots(int NMOD) {
        if (MOD == NMOD && (int)root.size() >= N) return;
        assert(MOD == NMOD);


        int cN = max(N, 1 << 17);
        rev.resize(cN);
        root.resize(cN);
        for (int i = 1; i < cN; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (cN / 2));
        int croot = 2;
        while (!(bin(croot, cN) == 1 && bin(croot, cN / 2) != 1)) croot++;
        int cur = 1;
        for (int i = cN >> 1; i < cN; i++) {
            root[i] = cur;
            cur = 1LL * cur * croot % MOD;
        }
        for (int i = (cN >> 1) - 1; i >= 1; i--) {
            root[i] = root[i * 2];
        }
    }

    void prepAB(std::vector<int> &A, std::vector<int> &B, int NMOD) {
        N = 1;
        while (N < (int)(A.size() + B.size())) N <<= 1;
        while ((int)A.size() < N) A.push_back(0);
        while ((int)B.size() < N) B.push_back(0);
        prepRoots(NMOD);
    }

    void fft(std::vector<int> &f) {
        for (int i = 0; i < N; i++) {
            int j = rev[i] >> __builtin_ctz(root.size() / N);
            if (i < j) std::swap(f[i], f[j]);
        }
        for (int k = 1; k < N; k <<= 1) {
            for (int i = 0; i < N; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    int z = 1LL * f[i + j + k] * root[j + k] % MOD;
                    f[i + j + k] = (f[i + j] - z + MOD) % MOD;
                    f[i + j] = (f[i + j] + z) % MOD;
                }
            }
        }
    }

    std::vector<int> mulMod(std::vector<int> a, std::vector<int> b, int NMOD = MOD) {
        int rsz = a.size() + b.size() - 1;
        bool eq = a == b;
        prepAB(a, b, NMOD);

        fft(a);
        if (eq) {
            b = a;
        } else {
            fft(b);
        }
        int oN = inv(N);
        for (int i = 0; i < N; i++) {
            a[i] = 1LL * a[i] * b[i] % MOD * oN % MOD;
        }
        reverse(a.begin() + 1, a.begin() + N);
        fft(a);
        a.resize(rsz);

        return a;
    }
}


struct poly : vector<int> {
    using vector<int>::vector;
    poly(const vector<int> &a) : vector<int>(a) {}
    poly(int x) : vector<int>(1, x) {}

    int& operator[](int id) {
        if (id >= (int)size()) resize(id + 1);
        assert(id >= 0 && id < (int)size());
        return vector<int>::operator[](id);
    }

    int operator[](int id) const {
        assert(id >= 0);
        if (id < (int)size()) return vector<int>::operator[](id);
        return 0;
    }

    poly operator+ (const poly &b) {
        const poly &a = *this;
        poly c(max(a.size(), b.size()));
        for (int i = 0; i < (int)c.size(); i++) {
            c[i] = (a[i] + b[i]) % MOD;
        }
        return c;
    }

    poly operator- (const poly &b) {
        const poly &a = *this;
        poly c(max(a.size(), b.size()));
        for (int i = 0; i < (int)c.size(); i++) {
            c[i] = (a[i] - b[i] + MOD) % MOD;
        }
        return c;
    }

    poly operator* (int d) const {
        poly res = *this;
        for (int i = 0; i < (int)size(); i++) {
            res[i] = 1LL * res[i] * d % MOD;
        }
        return res;
    }

    poly operator/ (int d) const {
        poly res = *this;
        d = ::inv(d);
        for (int i = 0; i < (int)size(); i++) {
            res[i] = 1LL * res[i] * d % MOD;
        }
        return res;
    }

    poly operator/= (int d) {
        return *this = *this / d;
    }

    poly operator* (const poly &p) const {
        return poly(fft::mulMod(*this, p, MOD));
    }

    poly operator*= (const poly &p) {
        return *this = *this * p;
    }

    poly inv() const {
        assert((*this)[0] != 0);
        poly r(1, ::inv((*this)[0]));
        for (int n = 1; n < (int)size(); n <<= 1) {
            poly ca = cut(2 * n);
            r = (r * 2 - r * r * ca).cut(2 * n);
        }
        r.resize(size());
        return r;
    }

    poly cut(int n) const {
        poly res = *this;
        res.resize(n);
        return res;
    }
};

int main() {
    const int N = 2e5 + 1;

    poly a, b;
    a.resize(N);
    b.resize(N);
    for (int i = -N; i <= N; i++) {
        ll id1 = 1LL * 2 * i * i + i;
        ll id2 = 4 * (1LL * 3 * i * i - i) / 2;
        if (0 <= id1 && id1 < N) add(a[id1], 1);
        if (0 <= id2 && id2 < N) add(b[id2], i % 2 == 0 ? 1 : MOD-1);
    }
    auto dp = a * b.inv().cut(N);

    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", dp[n]);
    }
}

