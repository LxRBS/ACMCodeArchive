#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int k;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
struct graphgame{
    int n,m,s;
    vector<vector<int> > G,rG;
    vector<int> f,cnt;
    void read()
    {
        G.clear(); rG.clear();
        scanf("%d%d%d",&n,&m,&s); s--;
        G.resize(n); rG.resize(n);
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v); u--; v--;
            G[u].push_back(v); rG[v].push_back(u);
        }
    }
    int solve()
    {
        f.clear(); cnt.clear();
        f.resize(n); cnt.resize(n);
        queue<int> que;
        for(int i=0;i<n;i++) f[i]=cnt[i]=0;
        for(int i=0;i<n;i++) if(G[i].size()==0) {f[i]=-1; que.push(i);}
        while(que.size())
        {
            int v=que.front(); que.pop();
            assert(f[v]!=0);
            if(f[v]<0)// losing
            {
                for(auto to:rG[v])
                    if(f[to]==0) {f[to]=-f[v]+1; que.push(to);}
            }
            else //winning
            {
                for(auto to:rG[v])
                {
                    cnt[to]++;
                    if(f[to]==0&&cnt[to]==(int)G[to].size())
                    {
                        f[to]=-f[v]-1;
                        que.push(to);
                    }
                }
            }
        }
        return f[s];
    }
}g;
vector<int> pos,neg;
int T,drawcnt,ans;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        pos.clear(); neg.clear(); drawcnt=0;
        scanf("%d",&k);
        for(int i=0;i<k;i++)
        {
            g.read();
            int val=g.solve();
            if(val>0) pos.push_back(val); else if(val<0) neg.push_back(-val); else drawcnt++;
        }
        sort(pos.begin(),pos.end()); sort(neg.begin(),neg.end());
        int ans=0;
        for(int i=0;i<(int)pos.size();i++)
        {
            int cnt=drawcnt+(int)(pos.size()-1-i)+neg.end()-lower_bound(neg.begin(),neg.end(),pos[i]);
            add(ans,pow_mod(2,cnt));
        }
        printf("%d\n",ans);
    }
    return 0;
}
