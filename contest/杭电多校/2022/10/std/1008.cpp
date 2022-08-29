#include<cstdio>
#include<vector>

using namespace std;


vector<int> ed[600000];
int dfn[600000],rev[600000],dep[600000],E[1100000],ecnt,epos[600000],sz[600000];

void dfs_bas(int u,int f)
{
    dfn[u]=++dfn[0];rev[dfn[u]]=u;
    dep[u]=dep[f]+1;E[++ecnt]=u;
    epos[u]=ecnt;
    sz[u]=1;
    for(int i=0;i<ed[u].size();i++)
    {
        int v=ed[u][i];if(v==f)continue;
        dfs_bas(v,u);E[++ecnt]=u;
        sz[u]+=sz[v];
    }
}
struct ST
{
    int lg[1100000],c[1100000][20];
    void init(int n)
    {
        lg[0]=-1;for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
        for(int i=1;i<=n;i++)c[i][0]=E[i];
        for(int j=1;(1<<j)<=n;j++)
        {
            for(int i=1;i+(1<<j)-1<=n;i++)
            {
                int x=c[i][j-1],y=c[i+(1<<(j-1))][j-1];
                c[i][j]=dep[x]<dep[y]?x:y;
            }
        }
    }
    int query(int l,int r)
    {
        int len=lg[r-l+1];int x=c[l][len],y=c[r-(1<<len)+1][len];
        return dep[x]<dep[y]?x:y;
    }
}SSS;
int LCA(int x,int y)
{
    if(epos[x]>epos[y])swap(x,y);return SSS.query(epos[x],epos[y]);
}
int dis(int x,int y)
{
	int l=LCA(x,y);return dep[x]+dep[y]-2*dep[l];
}

struct BCJ
{
	int fa[200000];int a[200000],b[200000],d[200000];
	void init(int n){for(int i=1;i<=n;i++)fa[i]=a[i]=b[i]=i,d[i]=0;}
	int fnd(int x){return x==fa[x]?x:fa[x]=fnd(fa[x]);}
	void conn(int x,int y)
	{
		x=fnd(x),y=fnd(y);if(x==y)return;
		int s[4]={a[x],a[y],b[x],b[y]};
		d[x]=-1;
		for(int i=0;i<4;i++)for(int j=i+1;j<4;j++)
		{
			int t=dis(s[i],s[j]);if(t>d[x])d[x]=t,a[x]=s[i],b[x]=s[j];
		}
		fa[y]=x;
	}
}B;

int cnt[200000],U[200000],V[200000];

int main()
{
	//freopen("1008.in","r",stdin);
	//freopen("1008.out","w",stdout);
	int TT=0;scanf("%d",&TT);
	while(TT--)
	{
		int n=0,m=0;scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&U[i],&V[i]);ed[U[i]].push_back(V[i]),ed[V[i]].push_back(U[i]);
		}
		for(int i=1;i<=n;i++)if(!dfn[i])dfs_bas(i,0);
		SSS.init(ecnt);
		B.init(n);cnt[0]=n;int maxd=0;
		for(int i=1;i<=m;i++)
		{
			int x=B.fnd(U[i]),y=B.fnd(V[i]);cnt[B.d[x]]--,cnt[B.d[y]]--;
			B.conn(x,y);cnt[B.d[x]]++;maxd=max(maxd,B.d[x]);
			
			int p=maxd;if(p&1)p++;
			int t=cnt[p]+cnt[p-1];
			if(t>=3){printf("%d\n",p+2);}
			else if(t==2){printf("%d\n",p+1);}
			else
			{
				if(p==maxd)printf("%d\n",p);
				else
				{
					if(cnt[maxd-1]||(maxd-2>=0&&cnt[maxd-2]))
					{
						printf("%d\n",p);
					}
					else
					{
						printf("%d\n",p-1);
					}
				}
			}
		}
		
		for(int i=0;i<=ecnt;i++)E[i]=0;ecnt=0;
		for(int i=0;i<=n;i++)dfn[i]=cnt[i]=0,ed[i].clear();
	}
}