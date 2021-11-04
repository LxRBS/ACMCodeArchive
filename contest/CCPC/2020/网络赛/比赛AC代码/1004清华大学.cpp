#include<bits/stdc++.h>
#define L long long
#define vi vector<int>
#define pb push_back
using namespace std;
int t,n,m,r,b,x[1000010],f[1000010],w[1000010];
vi a[1000010],c[1000010];
bool u[1000010];
inline void dfs(int i)
{
    int j;
    for(auto j:a[i])
        if(!f[j])
        {
            x[j]--;
            if(!x[j] || u[j])
            {
                f[j]=f[i];
                dfs(j);
            }
        }
}
int main()
{
    int i,j,k;
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++)
    {
        scanf("%d%d%d%d",&n,&m,&r,&b);
        while(b--)
        {
            scanf("%d",&i);
            u[i]=1;
        }
        for(i=1;i<=n;i++)
        {
            scanf("%d",&w[i]);
            c[w[i]].pb(i);
        }
        for(i=1;i<=m;i++)
        {
            scanf("%d%d",&j,&k);
            a[k].pb(j);
            x[j]++;
        }
        for(i=r;i>0;i--)
            for(auto j:c[i])
                if(!f[j])
                {
                    f[j]=w[j];
                    dfs(j);
                }
        printf("Case #%d:\n",tt);
        for(i=1;i<n;i++)
            printf("%d ",f[i]);
        printf("%d\n",f[n]);
        for(i=1;i<=n;i++)
            u[i]=0,a[i].clear(),x[i]=0,f[i]=0;
        for(i=1;i<=r;i++)
            c[i].clear();
    }
    return 0;
}