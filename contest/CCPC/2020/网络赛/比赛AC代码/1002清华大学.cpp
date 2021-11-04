#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#ifdef whzzt 
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) ((void)0)
#endif
using namespace std;
using i128 = __int128;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;
namespace ds {
    #define inc inc_it
    #define dec dec_it
    int mod;
    inline void inc(int &a, int b){ (a += b) < mod ?: a -= mod; }
    inline void inc(int &a, i64 b){ a = (a + b) % mod; }
    inline void dec(int &a, int b){ (a -= b) >= 0 ?: a += mod; }
    inline void dec(int &a, i64 b){ inc(a, mod - b % mod); }
    int fpow(int a, int t){
        static int r;
        for (r = 1; t; t >>= 1, a = (i64)a * a % mod) if (t & 1) r = (i64)r * a % mod;
        return r;
    }
    const int unit = 7;
    i64 x;
    int B, S, RS, size, count, fac[unit], ifac[unit], inv[unit], remain;
    vector<int> primes, pi;
    struct array_t {
        int f[unit];
        array_t(){ memset(f, 0, unit * 4); }
        int &operator[](int i){ return f[i]; }
        int to_val(){
            int sum = 0;
            for (int i = 0; i < unit; ++i) inc(sum, (i64)f[i] * ifac[i]);
            return sum;
        }
    } ;
    inline void inc(array_t &a, array_t &b){
        for(int i = 0; i < unit; ++i) if (b[i]) inc(a[i], b[i]);
    }
    inline void inc(array_t &a, array_t &b, int v){
        for(int i = 0; i + 1 < unit; ++i) if (b[i]) inc(a[i + 1], (i64)b[i] * v);
    }
    template<class value_t>
    struct data_t {
        vector<value_t> lsum, ssum;
        data_t(){ lsum.resize(size), ssum.resize(size); }
        void update(int p, vector<int> g){
            int i, j, e, l = S / p;
            for (i = 1; i <= S; ++i) dec(ssum[i], lsum[S]);
            for (i = S; i >= 2; --i) dec(lsum[i], lsum[i - 1]);
            for (i = 1; i <= S; ++i) for (j = i, e = 0; j <= l; inc(ssum[i], (i64)ssum[j *= p] * g[++e]));
            for (i = 2; i <= S; ++i) dec(ssum[i - 1], ssum[i]);
            for (i = S; i >= 1; --i) if (lsum[i]) {
                for (j = i, e = 0; j <= l; inc(lsum[j *= p], (i64)lsum[i] * g[++e]));
                for (j = x / p / j; j; j /= p) inc(ssum[j], (i64)lsum[i] * g[++e]);
            }
            for (i = 2; i <= S; ++i) inc(lsum[i], lsum[i - 1]);
            inc(ssum[S], lsum[S]);
            for (i = S; i >= 2; --i) inc(ssum[i - 1], ssum[i]);
        }
        void gsum(){
            int i;
            for (i = 2; i <= S; ++i) inc(lsum[i], lsum[i - 1]);
            inc(ssum[S], lsum[S]); if (S == RS) lsum[S] = ssum[S];
            for (i = S; i >= 2; --i) inc(ssum[i - 1], ssum[i]);
        }
        void gdif(){
            int i;
            for (i = 2; i <= S; ++i) dec(ssum[i - 1], ssum[i]);
            dec(ssum[S], lsum[S]);
            for (i = S; i >= 2; --i) dec(lsum[i], lsum[i - 1]);
        }
        void add(i64 a, value_t b){ inc(a <= S ? lsum[a] : ssum[x / a], b); }
        void print(){
            debug("function address %llu: \n", u64(this));
            for (int i = 1; i <= S; ++i) debug("S(%d) = %d\n", i, lsum[i]);
            for (int i = S; i >= 1; --i) debug("S(%llu) = %d\n", x / i, ssum[i]);
        }
    } ;
    void init(){
        primes.clear(), pi.clear(), remain = size = count = 0;
        int i, j;
        S = sqrtl(x), RS = x / S, size = S + 1, B = powl(x, 1.0 / unit) + 1e-7, pi.resize(size);
        vector<char> sieve(size);
        for (fac[0] = i = 1; i < unit; ++i) fac[i] = (i64)fac[i - 1] * i;
        for (inv[1] = 1, i = 2; i < unit; ++i) inv[i] = mod - (i64)(mod / i) * inv[mod % i] % mod;
        for (ifac[0] = i = 1; i < unit; ++i) ifac[i] = (i64)ifac[i - 1] * inv[i] % mod;
        for (i = 4; i <= S; i += 2) sieve[i] = true;
        for (i = 9; i <= S; i += 6) sieve[i] = true;
        for (i = 5; i * i <= S; i += 2) if (!sieve[i]) {
            for (j = i * i; j <= S; j += 6 * i) sieve[j] = true;
            for (j = i * (i + 6 - 2 * (i % 3)); j <= S; j += 6 * i) sieve[j] = true;
        }
        primes.pb(0);
        for (i = 2; i <= S; ++i) {
            pi[i] = pi[i - 1] + !sieve[i];
            if (!sieve[i]) (remain += i) %= mod, primes.pb(i), ++count;
        }
        primes.pb(size);
    }
    data_t<int> solve(vector<vector<int>> f){
        vector<vector<int>> g(count + 1), h(count + 1);
        int i, j, k, l, v, m;
        for (i = 1; i <= count; ++i) {
            m = f[i].size(), g[i].resize(m), h[i].resize(m);
            if (i > pi[B]) {
                for (g[i][0] = j = 1; j < m; ++j) g[i][j] = (i64)g[i][j - 1] * f[i][1] % mod;
                for (j = 0; j < m; ++j) g[i][j] = (i64)g[i][j] * ifac[j] % mod;
            } else g[i] = f[i];
            for (j = 0; j < m; ++j) for (h[i][j] = f[i][j], k = 0; k < j; ++k) dec(h[i][j], (i64)h[i][k] * g[i][j - k]);
        }
        data_t<int> F, G;
        vector<int> fval(count + 1);
        for (i = 1; i <= count; ++i) fval[i] = g[i][1];
        for (i = 1; i <= count; ++i) inc(fval[i], fval[i - 1]);
        {
            data_t<array_t> ts;
            i64 block = std::max((i64)S, std::min(x, i64(powl(x, 2.0 / 3) * 9)));
            block = x / (x / block);
            vector<i64> nxt(size);
            function<void(int, i64, int, int)> dfs = [&](int pos, i64 cur, int cnt, int now){
                int i, u, l, r;
                for (i = pos; cur * primes[i] * primes[i] <= block; ++i) {
                    i64 t = cur, a;
                    int e = 0, b;
                    while (t * primes[i] * primes[i] <= block) {
                        t *= primes[i], ++e;
                        dfs(i + 1, t, cnt + e, (i64)now * g[i][e] % mod);
                        a = t * primes[i], b = (i64)now * g[i][e + 1] % mod * fac[cnt + e + 1] % mod;
                        if (a <= S) nxt[a] = a, inc(ts.lsum[a][cnt + e + 1], b);
                        else inc(ts.ssum[x / a][cnt + e + 1], b);
                    }
                }
                now = (i64)now * fac[cnt + 1] % mod;
                for (i = pos; cur * primes[i] <= S; ++i) {
                    u = cur * primes[i], nxt[u] = u;
                    inc(ts.lsum[u][cnt + 1], (i64)now * (fval[i] + mod - fval[i - 1]));
                }
                i64 m = x / cur;
                l = i, r = count;
                if (cur * S > block) r = pi[block / cur];
                for (u = l; u <= r; ++u) inc(ts.ssum[m / primes[u]][cnt + 1], (i64)now * (fval[u] + mod - fval[u - 1]));
            } ;
            dfs(pi[B] + 1, 1, 0, 1);
            ++ts.lsum[nxt[1] = 1][0];
            ts.gsum();
            for (i = 1; i <= S; ++i) if (!nxt[i]) nxt[i] = nxt[i - 1];
            l = x / block - 1;
            for (i = l; i >= 1; --i) {
                i64 m = x / i;
                array_t sum;
                sum[0] = 1;
                for (j = pi[B] + 1; (i64)i * primes[j] <= S && j <= count; ++j) inc(sum, ts.ssum[i * primes[j]], fval[j] + mod - fval[j - 1]);
                for (; (i64)primes[j] * primes[j] <= m && j <= count; ++j) inc(sum, ts.lsum[m / primes[j]], fval[j] + mod - fval[j - 1]);
                for (; j <= count; j = v + 1) {
                    k = nxt[m / primes[j]];
                    v = (i64)k * S > m ? pi[m / k] : count;
                    inc(sum, ts.lsum[k], fval[v] + mod - fval[j - 1]);
                }
                ts.ssum[i] = sum;
            }
            for (i = 1; i <= S; ++i) G.lsum[i] = ts.lsum[i].to_val(), G.ssum[i] = ts.ssum[i].to_val();
        }
        for (i = pi[B]; i >= 1; --i) G.update(primes[i], g[i]);
        {
            vector<pair<i64, int>> vh;
            function<void(int, i64, int)> search = [&](int pos, i64 rem, int now){
                vh.emplace_back(x / rem, now);
                while ((i64)primes[pos] * primes[pos] <= rem) {
                    i64 t = rem / primes[pos] / primes[pos];
                    int e = 2;
                    for (; t; t /= primes[pos], ++e) if (h[pos][e]) search(pos + 1, t, (i64)now * h[pos][e] % mod);
                    ++pos;
                }
            } ;
            search(1, x, 1);
            sort(vh.begin(), vh.end());
            for (i = 0; i + 1 < vh.size(); ++i) if (vh[i].first == vh[i + 1].first) inc(vh[i + 1].second, vh[i].second), vh[i].second = 0;
            vector<pair<i64, int>> vv;
            for (i = 0; i < vh.size(); ++i) if (vh[i].second) vv.pb(vh[i]);
            vh.swap(vv), vv.clear();
            vh.emplace_back(x + 1, 0);
            vector<int> hsum(RS + 1), hcnt(size), nxt(size);
            for (auto it : vh) inc(it.first > S ? hsum[x / it.first] : hcnt[it.first], it.second);
            for (i = RS - 1; i >= 1; --i) inc(hsum[i], hsum[i + 1]);
            for (i = 1; i <= S; ++i) inc(hcnt[i], hcnt[i - 1]); 
            nxt[S] = S;
            for (i = S - 1; i >= 1; --i) nxt[i] = hcnt[i] == hcnt[i + 1] ? nxt[i + 1] : i;
            i64 low = pow(x, 0.6);
            low = x / (x / low);
            for (j = 0; vh[j].first <= low; ++j) {
                for (i = 1; i * vh[j].first <= S; ++i) inc(F.lsum[i * vh[j].first], (i64)vh[j].second * (G.lsum[i] + mod - G.lsum[i - 1]));
                for (i64 it = x / vh[j].first; i * vh[j].first <= low && i <= S; ++i) inc(F.ssum[it / i], (i64)vh[j].second * (G.lsum[i] + mod - G.lsum[i - 1]));
            }
            F.gsum(), low = std::min(x / low, S + 1LL);
            for (i = S; i >= low; --i) for (j = 0; i * vh[j].first <= S; ++j) inc(F.ssum[i], (i64)vh[j].second * (G.ssum[i * vh[j].first] + mod - G.lsum[S]));
            for (i = low - 1; i >= 1; --i) {
                int w = 0;
                i64 m = x / i;
                for (j = 0; i * vh[j].first <= S; ++j) inc(w, (i64)vh[j].second * G.ssum[i * vh[j].first]);
                for (; vh[j].first <= S; ++j) inc(w, (i64)vh[j].second * G.lsum[m / vh[j].first]);
                for (j = 1; i * (j + 1) <= RS && j <= S; ++j) inc(w, (i64)G.lsum[j] * (hsum[i * j] + mod - hsum[i * (j + 1)]));
                if (j <= S) inc(w, (i64)G.lsum[j] * hsum[i * j]);
                F.ssum[i] = w;
            }
        }
        return F;
    }
    struct lagrange{
        vector<int> init, coef;
        int n;
        lagrange(vector<int> init): init(init){
            int i;
            coef.resize(n = init.size());
            vector<int> ifac(n), inv(n);
            for (ifac[0] = i = 1; i < n; ++i) {
                inv[i] = i > 1 ? mod - (i64)inv[mod % i] * (mod / i) % mod : 1;
                ifac[i] = (i64)ifac[i - 1] * inv[i] % mod;
            }
            for (i = 0; i < n; ++i) {
                coef[i] = (i64)init[i] * ifac[n - i - 1] % mod * ifac[i] % mod;
                if ((n & 1) == (i & 1)) coef[i] = mod - coef[i];
            }
        }
        int get(i64 w){
            int x = w % mod; 
            if (x < n) return init[x];
            int res = 0, a = 1, i;
            for (i = 0; i < n; ++i) {
                res = ((i64)res * (x - i) + (i64)a * coef[i]) % mod;
                a = (i64)a * (x - i) % mod;
            }
            return (res + mod) % mod;
        }
    };
    vector<vector<int>> generate(function<int(int, int)> func){
        int i, e;
        i64 t;
        vector<vector<int>> res(count + 1);
        for (i = 1; i <= count; ++i) for (res[i].pb(t = e = 1); t * primes[i] <= x; t *= primes[i], ++e) res[i].pb(func(primes[i], e));
        return res;
    }
    vector<vector<int>> conv(vector<vector<int>> a, vector<vector<int>> b){
        int i, j, k, l;
        decltype(a) c(count + 1);
        for (i = 1; i <= count; ++i) for (c[i].resize(l = a[i].size()), j = 0; j < l; ++j) for (k = 0; j + k < l; ++k) inc(c[i][j + k], (i64)a[i][j] * b[i][k]);
        return c;
    }
    data_t<int> primesum(int s){
        int i, j, e, L = std::max(s + 2, S);
        i64 t;
        vector<int> coef(L + 1);
        for (i = 1; i <= L; ++i) coef[i] = 1;
        for (i = 2; i <= L; ++i) if (coef[i] == 1) for (coef[i] = fpow(i, s), j = 2; i * j <= L; ++j) coef[i * j] = (i64)coef[i] * coef[j] % mod;
        vector<int> psum(coef.begin(), coef.begin() + s + 3);
        for (i = 1; i < psum.size(); ++i) inc(psum[i], psum[i - 1]);
        lagrange sol(psum);
        data_t<int> fw = solve(generate([=](int p, int e){ return fpow(p, e * s); }));
        for (i = 1; i <= S; ++i) fw.ssum[i] = (sol.get(x / i) + mod - fw.ssum[i]) % mod, fw.lsum[i] = 0;
        for (i = S; i >= 1; --i) for (j = 2; i * j <= S; ++j) dec(fw.ssum[i], (i64)coef[j] * fw.ssum[i * j]);
        return fw;
    } ;
}
int main(){
    int t;
    for (cin >> t; t; --t) {
        i64 n; int mod;
        cin >> n >> mod;
        ds::mod = mod, n += 1, ds::x = n, ds::init();
        int res = (i64)n % mod * ((n + 1) % mod) % mod * (mod / 2 + 1) % mod;
        res = ((res + ds::primesum(1).ssum[1] - 5) % mod + mod) % mod;
        res = (res + ds::remain) % mod;
        cout << res << '\n';
    }
}