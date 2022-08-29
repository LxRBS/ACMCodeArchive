#include<cstdio>
using namespace std;
int n,m,T,a[100005],deg[100005];
long long Ans[100005],Sum[100005];

int F[100005];
int Find(int x)
{
    return F[x] == x ? x : F[x] = Find(F[x]);
}
int main()
{
    // freopen("1004.in","r",stdin);
    // freopen("1005.out","w",stdout);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        // printf("-- T = %d (n,m) = %d %d\n",T,n,m);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            deg[i] = 0;
            F[i] = i;
            Sum[i] = Ans[i] = 0;
        }
        for(int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            deg[x]++;
            deg[y]++;
            if(Find(x) != Find(y))
                F[Find(x)] = Find(y);
        }
        for(int i=1;i<=n;i++)
        {
            Ans[Find(i)] += (long long)(deg[i]+1) * a[i];
            Sum[Find(i)] += (deg[i]+1);
        }
        for(int i=1;i<=n;i++)
        {
            printf("%.6lf\n",(double)((long double)Ans[Find(i)] / Sum[Find(i)]));
            // printf("%lld %lld\n",Ans[Find(i)],Sum[Find(i)]);
        }
    }
    
}