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
int n;
db c1,c2,a[MAXN];
int main()
{
    rep(T,1,read())
    {
        n=read();
        c1=c2=0;
        rep(i,1,n) 
        {
            a[i]=read();
            db x=0;
            if(c2>=200) c2+=0.5*a[i];
            else if(c2>=100) c2+=0.8*a[i];
            else c2+=a[i];
            if(c1<100) x=min(a[i],100-c1),c1+=x,a[i]-=x;
            if(a[i]>0&&c1<200) x=min(a[i]*0.8,200-c1),c1+=x,a[i]-=x/0.8;
            if(a[i]>0&&c1>=200) c1+=a[i]*0.5;
            //cout<<c1<<" "<<c2<<endl;
        }
        printf("%.3lf %.3lf\n",c1,c2);
    }
}
