#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define lowbit(x) x&-x
#define pb push_back
#define ALL(x) (x).begin(),(x).end()
#define UNI(x) sort(ALL(x)),x.resize(unique(ALL(x))-x.begin())
#define GETPOS(c,x) (lower_bound(ALL(c),x)-c.begin())
#define LEN(x) strlen(x)
#define MS0(x) memset((x),0,sizeof((x)))
#define Rint register int
#define ls (u<<1)
#define rs (u<<1|1)
typedef unsigned int unit;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> Vi;
typedef vector<ll> Vll;
typedef vector<pii> Vpii;
template<class T> void _R(T &x) { cin >> x; }
void _R(int &x) { scanf("%d", &x); }
void _R(ll &x) { scanf("%lld", &x); }
void _R(ull &x) { scanf("%llu", &x); }
void _R(double &x) { scanf("%lf", &x); }
void _R(char &x) { scanf(" %c", &x); }
void _R(char *x) { scanf("%s", x); }
void R() {}
template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
template<class T> void _W(const T &x) { cout << x; }
void _W(const int &x) { printf("%d", x); }
void _W(const ll &x) { printf("%lld", x); }
void _W(const double &x) { printf("%.16f", x); }
void _W(const char &x) { putchar(x); }
void _W(const char *x) { printf("%s", x); }
template<class T,class U> void _W(const pair<T,U> &x) {_W(x.fi);putchar(' '); _W(x.se);}
template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
void W() {}
template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }
const int MOD=1e9+7,mod=998244353;
ll qpow(ll a,ll b) {ll res=1;a%=MOD; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%MOD;a=a*a%MOD;}return res;}
const int MAXN=5e5+10,MAXM=1e7+10;
const int INF=INT_MAX,SINF=0x3f3f3f3f;
const ll llINF=LLONG_MAX;
const int inv2=(MOD+1)/2;
const int Lim=1<<20;

template <int _P>
struct Modint
{
    static constexpr int P=_P;
private :
    int v;
public :
    Modint() : v(0){}
    Modint(ll _v){v=_v%P;if(v<0)v+=P;}
    explicit operator int() const {return v;}
    explicit operator long long() const {return v;}
    explicit operator bool() const {return v>0;}
    bool operator == (const Modint &o) const {return v==o.v;}
    bool operator != (const Modint &o) const {return v!=o.v;}
    Modint operator - () const {return Modint(v?P-v:0);}
    Modint operator + () const {return *this;}
    Modint & operator ++ (){v++;if(v==P)v=0;return *this;}
    Modint & operator -- (){if(v==0)v=P;v--;return *this;}
    Modint operator ++ (int){Modint r=*this;++*this;return r;}
    Modint operator -- (int){Modint r=*this;--*this;return r;}
    Modint & operator += (const Modint &o){v+=o.v;if(v>=P)v-=P;return *this;}
    Modint operator + (const Modint & o)const{return Modint(*this)+=o;}
    Modint & operator -= (const Modint & o){v-=o.v;if(v<0)v+=P;return *this;}
    Modint operator - (const Modint &o)const {return Modint(*this)-=o;}
    Modint & operator *=(const Modint & o){v=(int)(((ll)v)*o.v%P);return *this;}
    Modint operator * (const Modint & o)const {return Modint(*this)*=o;}
    Modint & operator /= (const Modint & o){return (*this)*=o.Inv();}
    Modint operator / (const Modint & o)const{return Modint(*this)/=o;}
    friend Modint operator + (const Modint &x,const ll &o) {return x+(Modint)o;}
    friend Modint operator + (const ll &o,const Modint &x) {return x+(Modint)o;}
    friend Modint operator - (const Modint &x,const ll &o) {return x-(Modint)o;}
    friend Modint operator - (const ll &o,const Modint &x) {return (Modint)o-x;}
    friend Modint operator * (const Modint &x,const ll &o) {return x*(Modint)o;}
    friend Modint operator * (const ll &o,const Modint &x) {return x*(Modint)o;}
    friend Modint operator / (const Modint &x,const ll &o) {Modint c=o;return x*c.Inv();}
    friend Modint operator / (const ll &o,const Modint &x) {Modint c=o;return c*x.Inv();}
    Modint operator ^ (ll o)const{Modint r=1,t=v;while(o){if(o&1)r*=t;t*=t;o>>=1;}return r;}
    Modint operator ~ (){return (*this)^(P-2);}
    Modint Inv() const{return (*this)^(P-2);}
};

using mi=Modint<MOD>;

template<int P>
void _W(Modint<P> x){printf("%d",(int)x);}

template<int P>
void _R(Modint<P> &x){ll t;scanf("%lld",&t);x=t;}

mi dp[75][75][2][2],vis[75][75][2][2];;
ll t;
int s[75],k,b,d,n,m,c;

mi dfs(int dep,int tot,int lim,bool zero)
{
    if(dep==m+1&&tot==0)return 1;
    if(dep==m+1)return 0;
    if(tot<0)return 0;
    if(vis[dep][tot][lim][zero])return dp[dep][tot][lim][zero];
    vis[dep][tot][lim][zero]=1;
    int up=lim?s[dep]:b-1;
    int ct=0,i=0;
    int c=(i==d);
    if(zero&&(d==0))c=0;
    dp[dep][tot][lim][zero]+=dfs(dep+1,tot-c,lim&&(s[dep]==i),zero);
    ct++;
    if(i!=d&&d<=up)
    {
        ct++;
        i=d;
        int c=(i==d);
        if(zero&&(d==0))c=0;
        dp[dep][tot][lim][zero]+=dfs(dep+1,tot-c,lim&&(s[dep]==i),0);
    }
    if(i!=up)
    {
        ct++;
        i=up;
        dp[dep][tot][lim][zero]+=dfs(dep+1,tot,lim&&(s[dep]==i),zero&&(i==0));
    }
    dp[dep][tot][lim][zero]+=dfs(dep+1,tot,0,0)*max(0,up-ct+1);
    return dp[dep][tot][lim][zero];
}


mi calc(bool f)
{
    MS0(dp);MS0(vis);
    R(t);
    m=0;
    t-=f;
    while(t)
    {
        s[++m]=t%b;
        t/=b;
    }
    reverse(s+1,s+m+1);
    mi ans=0;
    for(int i=1;i<=m;i++)
    {
        mi t=i;
        ans+=dfs(1,i,1,1)*(t^k);
    }
    return ans;
}

void solve()
{
    R(k,b,d);
    mi ans=calc(1);
    ans=calc(0)-ans;
    W(ans);
}

int main()
{
    srand(time(0));
    int T=1;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        //printf("Case #%d: ",kase);
        solve();
    }
    return 0;
}