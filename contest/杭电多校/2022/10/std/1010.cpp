#include <bits/stdc++.h>
using namespace std;
#define fo(i,j,k) for(int i=(j),end_i=(k);i<=end_i;i++)
#define ff(i,j,k) for(int i=(j),end_i=(k);i< end_i;i++)
#define fd(i,j,k) for(int i=(j),end_i=(k);i>=end_i;i--)
#define all(x) (x).begin(),(x).end()
#define cle(x) memset(x,0,sizeof(x))
#define lowbit(x) ((x)&-(x))
#define VI vector<int>
#define ll long long
const ll mod=1e9+7;
inline ll Add(ll x,ll y){x+=y; return (x<mod)?x:x-mod;}
inline ll Dec(ll x,ll y){x-=y; return (x<0)?x+mod:x;}
inline ll Mul(ll x,ll y){return x*y%mod;}
inline ll Pow(ll x,ll y)
{
    y%=(mod-1);ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1) ans=ans*x%mod;
    return ans;
}
const int N=505;
int n;
struct matrix{
    ll a[N][N];
    matrix(){fo(i,0,n) fo(j,0,n) a[i][j]=0;}
    void clear(int n)
    {
        fo(i,0,n) fo(j,0,n) a[i][j]=0;
    }
    inline ll* operator [](int x){return a[x];}
};
inline ll det(matrix a,int n)
{
    ll d=1,inv,tmp;
    int flag=1;
    fo(i,1,n)
    {
        int k=i;
        fo(j,i+1,n) if(a[j][i]) {k=j; break;}
        if(k!=i) {fo(j,i,n) swap(a[k][j],a[i][j]); flag=-flag;}
        if(!a[i][i]) return 0;
        inv=Pow(a[i][i],mod-2);
        fo(j,i+1,n)
        {
            tmp=a[j][i]*inv%mod;
            fo(k,i,n) a[j][k]=Dec(a[j][k],a[i][k]*tmp%mod);
        }
        d=d*a[i][i]%mod;
    }
    if(flag==-1) d=(mod-d%mod)%mod;
    return d;
}
int r(matrix a)
{
    int d=0;
    ll inv,tmp;
    fo(i,1,n)
    {
        int k=i;
        fo(j,i+1,n) if(a[j][i]) {k=j; break;}
        if(k!=i) fo(j,i,n) swap(a[i][j],a[k][j]);
        if(!a[i][i]) continue;
        d++;
        inv=Pow(a[i][i],mod-2);
        fo(j,i+1,n)
        {
            tmp=a[j][i]*inv%mod;
            fo(k,i,n) a[j][k]=Dec(a[j][k],a[i][k]*tmp%mod);
        }
    }
    return d;
}
ll l[N],p[N];
inline void solve(matrix a,ll *p)
{
    static ll c[N][N],d[N][N];
    fo(i,0,n) fo(j,0,n) c[i][j]=d[i][j]=0;
    auto check = [&](const int &id,ll *g){
        fo(i,1,n) p[i]=0;
        p[id]=1;
        ll tmp;
        fd(i,n,1)
            if(l[i])
            {
                if(!c[i][i])
                {
                    fd(j,i,1) c[i][j]=l[j];
                    fo(j,1,n) d[i][j]=p[j];
                    return 0;
                }
                tmp=Pow(c[i][i],mod-2)*l[i]%mod;
                fd(j,i,1) l[j]=Dec(l[j],c[i][j]*tmp%mod);
                fo(j,1,n) p[j]=Dec(p[j],d[i][j]*tmp%mod);
            }
        fo(i,1,n) g[i]=p[i];
        return 1;
    };
    fo(i,1,n)
    {
        fo(j,1,n)
            l[j]=a[j][i];
        if(check(i,p)) return;
    }
}
void solve(matrix A)
{
    int rank=r(A);
    assert(rank!=n);
    {
        matrix B,C;
        static ll x[N],y[N];
        C.clear(n);
        fo(i,1,n) fo(j,1,n) C[j][i]=A[i][j];
        solve(A,y);
        solve(C,x);
        int c=0,r=0;
        fo(i,1,n) if(y[i]) {c=i; break;}
        fo(i,1,n) if(x[i]) {r=i; break;}
        B.clear(n-1);
        fo(i,1,n)
            if(i!=r)
                fo(j,1,n)
                    if(j!=c)
                        B[i-(i>r)][j-(j>c)]=A[i][j];
        ll tmp=det(B,n-1);
        tmp=((r+c)%2==1)?(mod-tmp)%mod:tmp;
        tmp=Pow(y[c]*x[r]%mod,mod-2)*tmp%mod;
        fo(i,1,n)
            printf("%lld%c",tmp*x[i]%mod*y[i]%mod,(i==n)?'\n':' ');
        return;
    }
}
void solve()
{
    int m,x,y;
    scanf("%d%d",&n,&m);
    if(n==1) {printf("1\n"); return;}
    matrix A;
    fo(i,1,m)
    {
        scanf("%d%d",&x,&y);
        A[y][y]++;
        A[x][y]--;
    }
    fo(i,1,n) fo(j,1,n) if(A[i][j]<0) A[i][j]+=mod;
    solve(A);
}
int main()
{
    int T; scanf("%d",&T);
    while(T--) solve();
    return 0;
}