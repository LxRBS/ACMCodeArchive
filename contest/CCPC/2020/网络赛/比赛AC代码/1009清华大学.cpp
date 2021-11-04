#include <bits/stdc++.h>

#define pb push_back
#define lowbit(x) ((x) & -(x))
#define fi first
#define se second

using namespace std;

using i128 = __int128;
using i64 = long long;
using u64 = unsigned long long; 

int P;
namespace nt {
    struct random_t {
        u64 s0, s1;
        random_t(){
            s0 = size_t(new char) xor time(nullptr);
            s1 = size_t(new char) xor (s0 + time(nullptr));
        }
        random_t(u64 s0, u64 s1):s0(s0), s1(s1){}
        u64 get(){
            std::swap(s0, s1);
            s1 ^= s1 << 23, s1 ^= (s1 >> 17) ^ s0 ^ (s0 >> 26);
            return s0 + s1;
        }
        int randint(int L, int R){
            return get() % (R - L + 1) + L;
        }
        i64 rand64(i64 L, i64 R){
            return get() % (R - L + 1) + L;
        }
    } rnd;
    void ensure(bool f){
        if (!f) throw "failed";
    }
    void ensuref(bool f, const char *message){
        if (!f) throw message;
    }
    template<class T> void exgcd(T a, T b, T &x, T &y){
        if (!b) return (void)(x = 1, y = 0);
        exgcd(b, a % b, y, x), y -= a / b * x;
    }
    template<class T> T Inv(T a, T mod){
        T x, y;
        exgcd(a, mod, x, y);
        return (x % mod + mod) % mod;
    }
    i64 fpow(i64 a, i64 t, i64 mod){
        i64 r = 1;
        for (; t; t >>= 1, a = (i128)a * a % mod) if (t & 1) r = (i128)r * a % mod;
        return r;
    }
    i64 gcd(i64 a, i64 b){
        #define ctz __builtin_ctzll
        if (!a || !b) return a | b;
        int shift = ctz(a | b);
        for (b >>= ctz(b); a; a -= b) if ((a >>= ctz(a)) < b) std::swap(a, b);
        return b << shift;
    }
    i64 congruence(i64 a, i64 b, i64 mod){
        // ax % mod = b
        i64 d = gcd(a, mod);
        if (b % d) return -1;
        i64 x, y;
        exgcd(a, mod, x, y);
        x = (i128)(b / d) * x % (mod / d);
        if (x < 0) x += mod / d;
        return x;
    }
    bool check_prime(i64 n){
        static const int jp[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        if (n == 1) return false;
        for (int p : jp) if (n % p == 0) return n == p;
        i64 r = n - 1, x, y;
        int e = 0;
        while (~r & 1) r >>= 1, ++e;
        for (int p : jp) {
            x = fpow(p, r, n);
            for (int t = 0; t < e && x > 1; ++t) {
                y = (i128)x * x % n;
                if (y == 1 && x != n - 1) return false;
                x = y;
            }
            if (x != 1) return false;
        }
        return true;
    }
    i64 find(i64 n){
        static const int step = 1 << 7;
        i64 x, y = rnd.randint(1, 32767) % n;
        int c = rnd.randint(1, 32767) % n;
        auto f = [=](i64 x){ return ((i128)x * x + c) % n; } ;
        for (int l = 1; ; l <<= 1) {
            x = y;
            for (int i = 0; i < l; ++i) y = f(y);
            for (int k = 0; k < l; k += step) {
                int e = std::min(step, l - k);
                i64 g = 1, z = y;
                for (int i = 0; i < e; ++i) g = (i128)g * ((y = f(y)) + n - x) % n;
                g = gcd(g, n);
                if (g == 1) continue;
                if (g == n) for (g = 1, y = z; g == 1; ) y = f(y), g = gcd(y + n - x, n);
                return g;
            }
        }
        throw "???";
    }
    void rho(i64 n, map<i64,int> &factor){
        while (~n & 1) n >>= 1, ++factor[2];
        if (n == 1) return ;
        if (check_prime(n)) {
            ++factor[n];
            return ;
        }
        i64 d;
        for (d = find(n); d == n; d = find(d));
        rho(d, factor), rho(n / d, factor);
    }
    int primitive_root(i64 mod){
        const int C = 10000;
        map<i64, int> factor;
        rho(mod - 1, factor);
        for (int g = 2; g <= C; ++g) {
            if (fpow(g, mod - 1, mod) != 1) continue;
            bool ok = true;
            for (auto o : factor) if (fpow(g, (mod - 1) / o.first, mod) == 1) { ok = false; break; }
            if (ok) return g;
        }
        throw "Error: no primitive root under C = 10000!";
    }
}
namespace fft {
typedef double ld;

const ld PI = acos(-1);

struct num {
  ld x, y;
  
  num(ld x = 0, ld y = 0) : x(x), y(y) {
  }

  num operator+(const num& o) const {
    return num(x + o.x, y + o.y);
  }

  num operator-(const num& o) const {
    return num(x - o.x, y - o.y);
  }

  num operator*(const num& o) const {
    return num(x * o.x - y * o.y, x * o.y + y * o.x);
  }
};

num conj(num a) {
  return num(a.x, -a.y);
}

vector<num> fa, fb, roots = {num(0, 0), num(1, 0)};
vector<int> rev = {0, 1};
int base = 1;

void ensure_base(int nbase) {
  if (nbase <= base) {
    return;
  }
  rev.resize(1 << nbase);
  for (int i = 0; i < (1 << nbase); ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nbase - 1));
  }
  roots.resize(1 << nbase);
  while (base < nbase) {
    ld angle = 2 * PI / (1 << (base + 1));
    for (int i = 1 << (base - 1); i < (1 << base); ++i) {
      roots[i << 1] = roots[i];
      ld ang = angle * ((i << 1) + 1 - (1 << base));
      roots[i << 1 | 1] = num(cos(ang), sin(ang));
    }
    ++base;
  }
}

void dft(vector<num>& a, int n) {
  int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; ++i) {
    if (i < (rev[i] >> shift)) {
      swap(a[i], a[rev[i] >> shift]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        num x = a[j + k], y = a[j + k + i] * roots[i + k];
        a[j + k] = x + y;
        a[j + k + i] = x - y;
      }
    }
  }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
  int need = a.size() + b.size() - 1, nbase = 0;
  while (1 << nbase < need) {
    ++nbase;
  }
  ensure_base(nbase);
  bool equal = a == b;
  int sz = 1 << nbase;
  if (sz > (int) fa.size()) {
    fa.resize(sz);
  }
  if (sz > (int) fb.size()) {
    fb.resize(sz);
  }
  for (int i = 0; i < (int) a.size(); i++) {
    int x = (a[i] % P + P) % P;
    fa[i] = num(x & ((1 << 15) - 1), x >> 15);
  }
  for (int i = (int) a.size(); i < sz; ++i) {
    fa[i] = num(0, 0);
  }
  dft(fa, sz);
  if (equal) {
    for (int i = 0; i < sz; ++i) {
      fb[i] = fa[i];
    }
  } else {
    for (int i = 0; i < (int) b.size(); ++i) {
      int x = (b[i] % P + P) % P;
      fb[i] = num(x & ((1 << 15) - 1), x >> 15);
    }
    for (int i = (int) b.size(); i < sz; ++i) {
      fb[i] = num(0, 0);
    }
    dft(fb, sz);
  }
  ld ratio = 0.25 / sz;
  num r1(1, 0), r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
  for (int i = 0; i <= sz >> 1; ++i) {
    int j = (sz - i) & (sz - 1);
    num a1 = (fa[i] + conj(fa[j])) * r1;
    num a2 = (fa[i] - conj(fa[j])) * r2;
    num b1 = (fb[i] + conj(fb[j])) * r3;
    num b2 = (fb[i] - conj(fb[j])) * r4;
    if (i != j) {
      num c1 = (fa[j] + conj(fa[i])) * r1;
      num c2 = (fa[j] - conj(fa[i])) * r2;
      num d1 = (fb[j] + conj(fb[i])) * r3;
      num d2 = (fb[j] - conj(fb[i])) * r4;
      fa[i] = c1 * d1 + c2 * d2 * r5;
      fb[i] = c1 * d2 + c2 * d1;
    }
    fa[j] = a1 * b1 + a2 * b2 * r5;
    fb[j] = a1 * b2 + a2 * b1;
  }
  dft(fa, sz);
  dft(fb, sz);
  vector<int> c(need);
  for (int i = 0; i < need; i++) {
    long long aa = fa[i].x + 0.5;
    long long bb = fb[i].x + 0.5;
    long long cc = fa[i].y + 0.5;
    c[i] = (aa + (bb % P << 15) + (cc % P << 30)) % P;
  }
  return c;
}
}

int main(){
    int t,o;
    for(o=1,scanf("%d",&t);o<=t;++o){
        int n,mod;
        scanf("%d%d",&n,&mod),P=mod;
        vector<int> f(mod),ind(mod),pos(mod);
        vector<int> fac(mod),ifac(mod),inv(mod);
        fac[0]=ifac[0]=fac[1]=ifac[1]=inv[1]=1;
        for(int i=2;i<mod;++i){
            fac[i]=(i64)fac[i-1]*i%mod;
            inv[i]=mod-(i64)(mod/i)*inv[mod%i]%mod;
            ifac[i]=(i64)ifac[i-1]*inv[i]%mod;
        }
        for(int i=0;i<=n;++i) scanf("%d",&f[i]);
        // obtain f[n+1]..f[p-1]
        vector<int> coef(n+1);
        for(int i=0;i<=n;++i){
            coef[i]=(i64)f[i]*ifac[i]%mod*ifac[n-i]%mod;
            if((n-i)&1) coef[i]=mod-coef[i];
        }
        vector<int> h=fft::multiply(coef,inv);
        for(int i=n+1;i<mod;++i) f[i]=(i64)h[i]*fac[i]%mod*ifac[i-n-1]%mod;
        // solve original polynomial
        int g=nt::primitive_root(mod),ig=inv[g];
        for(int c=1,i=0;i<mod-1;++i,c=(i64)c*g%mod) ind[c]=i,pos[i]=c;
        pos[mod-1]=1;
        vector<int> u(mod-1);
        for(int i=1;i<mod;++i) u[ind[i]]=f[i];
        vector<int> bin(mod*2);
        for(int i=0;i+1<bin.size();++i) bin[i+1]=(bin[i]+i)%(mod-1);
        vector<int> x(mod-1),y(2*mod-1);
        for(int i=0;i<mod-1;++i) x[i]=(i64)u[i]*pos[bin[i]]%mod;
        for(int i=0;i<2*mod-1;++i) y[i]=pos[mod-1-bin[i]];
        reverse(x.begin(),x.end());
        /*
        {
            vector<int> z(mod);
            for(int i=0;i<mod-1;++i)
                for(int j=0;j<mod-1;++j)
                {
                    z[i]=(z[i]+(i64)x[mod-2-j]*y[i+j])%mod;
                }
            for(int i=0;i<mod-1;++i) cerr<<(i64)z[i]*pos[bin[i]]%mod<<' '; cerr<<'\n';
        }*/
        vector<int> z=fft::multiply(x,y);
        vector<int> res(mod);
        for(int i=0;i<mod;++i) res[i]=(i64)(mod-z[i+mod-2])*pos[bin[i]]%mod;
        printf("Case #%d:\n",o);
        for(int i=0;i<=n;++i) printf("%d%c",res[i]," \n"[i==n]);
    }
}