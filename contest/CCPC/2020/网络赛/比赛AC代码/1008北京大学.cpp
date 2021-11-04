#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
    if(x>y)x=y;
}
typedef long long s64;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
struct P
{
    int x,y;
};
int sqr(int x)
{
    return x*x;
}
double dis(P a,P b)
{
    return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
const int N=50+5;
int n,x0,k[N];//s64 C[N][N]; 
double f[N][N],g[N][N][N][2];
P p[N][N];

int main()
{
    int tt;
    cin>>tt;
    rep(case_id,1,tt)
    {
        cin>>n>>x0;
        rep(i,1,n)scanf("%d",k+i);
        f[1][1]=g[1][1][1][0]=g[1][1][1][1]=1;
        rep(i,1,n)
        rep(j,1,i)p[i][j]={-i+2*j-1,i};
        rep(i,2,n)
        {
            rep(j,1,i)
            {
                f[i][j]=1e18;
                rep(k,1,i-1)chmin(f[i][j],dis(p[i][j],p[i-1][k])+g[i-1][k][k][0]);
            }
            int len=i-k[i]+1;
            rep(j,1,i-len+1)
            {
                g[i][j][j+len-1][0]=f[i][j];
                g[i][j][j+len-1][1]=f[i][j+len-1];
            }
            while(--len)
            {    
                double p=1.0*k[i]/(i-len+1);
                rep(l,1,i-len+1)
                {    
                    int r=l+len-1;
                    g[i][l][r][0]=p*f[i][l]+(1-p)*
                        min(l==1?1e18:2+g[i][l-1][r][0],r==i?1e18:2*(r+1-l)+g[i][l][r+1][1]);
                    g[i][l][r][1]=p*f[i][r]+(1-p)*
                        min(l==1?1e18:2*(r-l+1)+g[i][l-1][r][0],r==i?1e18:2+g[i][l][r+1][1]);
                }
            }
        }
        double ans=1e18;
        rep(k,1,n)chmin(ans,dis({x0,n+1},p[n][k])+g[n][k][k][0]);
        printf("%f\n",ans);
    }    
} 