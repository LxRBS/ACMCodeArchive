#include<cstdio>
#include<vector>
#include<cctype>
#include<string>
#include <iostream>

using namespace std;

const long long MOD=998244353,INV2=(MOD+1)>>1;
long long add(long long x,long long y){return x+y>=MOD?x+y-MOD:x+y;}
long long sub(long long x,long long y){return x>=y?x-y:x+MOD-y;}

vector<int> ed[3000000];
int fa[3000000],sz[3000000];
int dfn[3000000];

void dfs_bas(int u,int f)
{
    fa[u]=f,sz[u]=1,dfn[u]=++dfn[0];for(int i=0;i<ed[u].size();i++){if(ed[u][i]==f)continue;dfs_bas(ed[u][i],u);sz[u]+=sz[ed[u][i]];}
}

long long ans[3000000];
void upd(int l,int r,long long val){ans[l]=add(ans[l],val),ans[r+1]=sub(ans[r+1],val);}

struct BIT
{
    int c[3000000],n;
    int lowbit(int x){return x&-x;}
    void init(int N){n=N;for(int i=1;i<=n;i++)c[i]=0;}
    void add(int x){while(x<=n){c[x]++;x+=lowbit(x);}}
    int query(int x){int ans=0;while(x){ans+=c[x];x-=lowbit(x);}return ans;}
    int query(int x,int y){return query(y)-query(x-1);}
}B;

void work()
{
    //freopen("intelligence45.in","r",stdin);
    //freopen("intelligence45.out","w",stdout);
    int n;std::cin>>n;
    for(int i=1,x=0,y=0;i<n;i++)
    {
        std::cin>>x>>y;
ed[x].push_back(y),ed[y].push_back(x);
    }
    dfs_bas(1,0);B.init(n);
    for(int i=1;i<=n;i++)
    {
        //if(i%10==0)fprintf(stderr,"%d\n",i);
        //upd(dfn[i],dfn[i],sub(i-1,n-i));
        for(int j=0;j<ed[i].size();j++)
        {
            int u=ed[i][j];
            if(u==fa[i])
            {
                int c=sub(2*(B.query(1,dfn[i]-1)+B.query(dfn[i]+sz[i],n)),n-sz[i]);
                upd(dfn[i],dfn[i]+sz[i]-1,c);
            }
            else
            {
                int c=sub(2*B.query(dfn[u],dfn[u]+sz[u]-1),sz[u]);
                upd(1,n,c);upd(dfn[u],dfn[u]+sz[u]-1,sub(0,c));
            }
        }
        B.add(dfn[i]);
    }//fprintf(stderr,"A");
    for(int i=2;i<=n;i++)ans[i]=add(ans[i-1],ans[i]);
    //for(int i=1;i<=n;i++)printf("%lld ",ans[dfn[i]]);puts("");
    long long tot=(long long)n*(n-1)%MOD*INV2%MOD;
    for(int i=1;i<=n;i++)
    {
        std::cout<<(add(tot,ans[dfn[i]])*INV2%MOD)<<'\n';
    }
    for(int i=0;i<=n+1;i++)
    {
        ed[i].clear();fa[i]=sz[i]=dfn[i]=ans[i]=0;
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
    //freopen("1012.in","r",stdin);
    //freopen("1012.out","w",stdout);
    int TT=0;std::cin>>TT;
    while(TT--)
    {
        work();
    }
}