#include<bits/stdc++.h>
using namespace std;

typedef long long s64;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
const int N=500+5;
int n,k[N],a[N][N],b[N][N],c[N][N],d[N][N];
struct Pr
{
    int x,d;    
}; 
int F(int i,const Pr &p)
{
    if(i==n)return p.x;
    int j=lower_bound(a[i],a[i]+k[i],p.x+p.d)-a[i];
    return F(d[i][j],{p.x*c[i][j]+b[i][j],p.d*c[i][j]});
}
bool check()
{
    per(i,n-1,1)
    {
        rep(j,0,k[i]-1)
        {
            if(F(i,{a[i][j],0})!=F(i,{a[i][j],1}))return 0;
        }    
    }
    return 1;
}

int main()
{
    int tt;
    cin>>tt;
    rep(case_id,1,tt)
    {
        cin>>n;
        rep(i,1,n-1)
        {
            scanf("%d",k+i);
            rep(j,0,k[i]-1)scanf("%d%d%d%d",c[i]+j,b[i]+j,d[i]+j,a[i]+j);
            scanf("%d%d%d",c[i]+k[i],b[i]+k[i],d[i]+k[i]);    
        }    
        printf("Case #%d: ",case_id);
        puts(check()?"YES":"NO"); 
    }    
} 
