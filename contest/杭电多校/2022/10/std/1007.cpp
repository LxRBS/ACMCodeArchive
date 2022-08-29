#include<cstdio>
#include<vector>
using namespace std;
int n,T,siz[100005],cnt;
vector<int> vec[100005];
void dfs(int x,int y)
{
    siz[x] = 1;
    for(auto &p : vec[x])
    {
        if(p == y) continue;
        dfs(p,x);
        siz[x] += siz[p];
    }
    if(siz[x] % 2 == 0 && x!=1) cnt++;
}
int main()
{
    // freopen("1004.in","r",stdin);
    // freopen("1004.out","w",stdout);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            vec[i].clear();
        for(int i=1;i<=n-1;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            vec[x].push_back(y);
            vec[y].push_back(x);
        }
        cnt = 0;
        dfs(1,0);
        int ans = 1;
        for(int i=1;i<=cnt;i++)
            ans = ans * 2 % 998244353;
        printf("%d\n",ans-1);
    }
}