// #pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("O3")
#pragma GCC optimize("O2")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
// #pragma GCC optimize("trapv")
#include<bits/stdc++.h>
// #include <bits/extc++.h>
#define int long long
#define double long double
// #define i128 long long
// #define double long double
using namespace std;
 
#define rep(i,n) for (int i=0;i<(int)(n);++i)
#define rep1(i,n) for (int i=1;i<=(int)(n);++i)
#define range(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
 
typedef long long ll;
typedef unsigned long long ull;
// typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;


namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
// constexpr int bsf_constexpr(unsigned int n) {
//     int x = 0;
//     while (!(n & (1 << x))) x++;
//     return x;
// }

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal


template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    segtree(int n) : segtree(std::vector<S>(n, e())) {}
    segtree(const std::vector<S>& v) : _n((int)(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

using S=int;
S op(S l,S r){return l+r;}
S e(){return 0;}


int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
const int mod=998244353;
const int base[]={12321,32123};
const double EPS=1e-9;
const double pi=acos(-1);
const int INF=1e18;
const int N=100017;
mt19937 rng(1235);

int n,q;
int p[N];
int ans[N],C[N],now[N];
vector<pii> info[N];
int st[N];

int lowbit(int u){return u&(-u);}
void update(int u,int w){for (int i=u;i<=n+7;i+=lowbit(i)) C[i]+=w;}
int query(int u){int ans=0; for (int i=u;i;i-=lowbit(i)) ans+=C[i]; return ans;}
signed main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  int _;
  cin>>_;
  //_=1;
  while (_--){
    cin>>n>>q;
    rep(i,n) cin>>p[i];
    for (int i=1;i<=n+5;++i) C[i]=0,now[i]=0;
    rep(i,N) info[i].clear();
    p[n]=n+1;
    rep(i,q){
      int u,v;
      cin>>u>>v;
      u--, v--;
      info[u].pb({i,v});
    }
    int cnt=0;
    st[cnt++]=n; 
    auto upd=[&](int u){
      update(u+1,(now[u+1]?-1:1)), now[u+1]^=1;
      update(u+2,(now[u+2]?-1:1)), now[u+2]^=1;
    };
    for (int i=n-1;i>-1;--i){
      while (cnt&&p[i]>p[st[cnt-1]]) {
        cnt--; upd(st[cnt]);
      }
      st[cnt++]=i, upd(i);
      for (auto c:info[i]){
        int id=c.F, r=c.S;
        if (i==r) ans[id]=0;
        else ans[id]=(query(r+1)-query(i))/2;
      }
    }
    rep(i,q) cout<<ans[i]<<"\n";
  }
  return 0;
}