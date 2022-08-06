#include<bits/stdc++.h>
#define rep(i,s,t) for(int i=(s),i##end=(t);i<=i##end;++i)
#define dwn(i,s,t) for(int i=(s),i##end=(t);i>=i##end;--i)
#define ren for(int i=fst[x];i;i=nxt[i])
#define Fill(a,x) memset(a,x,sizeof(a))
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
const int inf=2139062143;
const int MOD=998244353;
const int MAXN=200100;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline ll readll()
{
    ll x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
namespace CALC
{
    inline int pls(int a,int b){return a+b>=MOD?a+b-MOD:a+b;}
    inline int mns(int a,int b){return a-b<0?a-b+MOD:a-b;}
    inline int mul(int a,int b){return (1LL*a*b)%MOD;}
    inline void inc(int &a,int b){a=pls(a,b);}
    inline void dec(int &a,int b){a=mns(a,b);}
    inline void tms(int &a,int b){a=mul(a,b);}
    inline int qp(int x,int t,int res=1)
        {for(;t;t>>=1,x=mul(x,x)) if(t&1) res=mul(res,x);return res;}
    inline int Inv(int x){return qp(x,MOD-2);}
}
using namespace CALC;
int n,a[MAXN],k,las,cur,l,r;
pair<ll,int> q[MAXN];
ll sum[MAXN],f[MAXN],mxf[MAXN];
ll mn[MAXN<<2];
void build(int k,int l,int r)
{
    if(l==r) {mn[k]=f[l];return ;}int mid=l+r>>1;
    build(k<<1,l,mid);build(k<<1|1,mid+1,r);
    mn[k]=min(mn[k<<1],mn[k<<1|1]);
}
int res=inf;
void query(int k,int l,int r,int a,int b,int w)
{
    if(a<=l&&r<=b)
    {
        if(mn[k]>w||res!=inf) return ;
        if(l==r) {res=l;return ;}int mid=l+r>>1;
        if(mn[k<<1]<=w) query(k<<1,l,mid,a,b,w);
        else if(mn[k<<1|1]<=w) query(k<<1|1,mid+1,r,a,b,w);
        return ;
    }
    int mid=l+r>>1;
    if(a<=mid) query(k<<1,l,mid,a,b,w);
    if(b>mid) query(k<<1|1,mid+1,r,a,b,w);
}
int solve()
{
    n=read(),a[0]=sum[0]=read(),k=min(read(),n);
    rep(i,1,n) a[i]=read(),sum[i]=sum[i-1]+a[i];
    f[0]=sum[0]<<1;rep(i,1,n) f[i]=max(sum[i]+a[i],f[i-1]);
    rep(i,0,n) f[i]=f[i]-sum[i];
    //rep(i,0,n) cout<<f[i]<<" ";puts("");
    build(1,1,n);
    las=-1,cur=0;
    while(cur!=n)
    {
        res=inf;
        query(1,1,n,cur+1,min(las+k+1,n),sum[cur]);
        //cout<<las<<" "<<cur<<" "<<res<<endl;
        if(res==inf) return 0;
        las=cur,cur=res;
    }
    return 1;
}
int main()
{
    rep(T,1,read()) puts(solve()?"YES":"NO");
}
