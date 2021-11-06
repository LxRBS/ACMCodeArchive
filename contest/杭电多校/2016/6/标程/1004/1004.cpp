#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

#define MAXN 100010
#define MAXM 1000010
typedef long long LL;

int n,m,q,r,qlen[MAXN];
int dfn[MAXN],def;
int que[MAXN];
int L[MAXN],fa[MAXN][20];
LL u[MAXM];

struct node
{
    int v;
    node *next;
}edge[MAXN*2];
node *cnt=&edge[0];
node *adj[MAXN];

void Addedge(int u,int v)
{
    node *p=++cnt;
    p->v=v;
    p->next=adj[u]; adj[u]=p;
}

void DFS(int u)
{
    dfn[u]=++def;
    for(node *p=adj[u];p;p=p->next){
        DFS(p->v);
    }
}


bool CMP(int a,int b)
{
    return dfn[a]<dfn[b];
}

void Getfather(int i)
{
    L[i]=L[fa[i][0]]+1;
    Addedge(fa[i][0],i);
    for(int j=1;(1 << j)<=n;++j)
        fa[i][j]=fa[fa[i][j-1]][j-1];
}

int LCA(int x,int y)
{
    int i,Lg;
    if(L[x]<L[y]){
        x+=y; y=x-y; x=x-y;
    }
    for(Lg=1;(1 << Lg)<=L[x];++Lg); --Lg;
    for(i=Lg;i>=0;--i)
        if(L[x]-(1 << i) >=L[y])
            x=fa[x][i];
    if(x==y) return x;
    for(i=Lg;i>=0;--i)
        if(fa[x][i] && fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}

void Init()
{
    memset(adj,0,sizeof(adj));
    cnt=&edge[0]; def=0;
    int i,k,f=-1; LL j;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;++i) scanf("%I64d",u+i);
    sort(u+1,u+1+m);
    for(i=1,j=0,k=1;i<=m;++i){
        while(u[i]>=j+k){
            if(f==-1) f=0;
            fa[k][0]=f; Getfather(k);
            j+=k++; f=-1;
        }
        if(u[i]-j+1!=k){
            if(f==-1) f=u[i]-j+1;
            else f=LCA(f,u[i]-j+1);
        }
    }
    while(k<=n){
        if(f==-1) f=0;
        fa[k][0]=f; Getfather(k);
        j+=k++; f=-1;
    }
}

void Query()
{
    int i,k,cnt,p; LL j;
    scanf("%d%d",&q,&r);
    for(i=1;i<=q;++i) scanf("%d",qlen+i);
    for(i=1;i<=r;++i) scanf("%I64d",u+i);
    sort(u+1,u+1+r);
    for(i=1,j=0,k=1;i<=r;++i){
        while(u[i]>=j+qlen[k]){
            sort(que+1,que+1+que[0],CMP);
            for(p=2,cnt=que[0]?L[que[1]]:0;p<=que[0];++p)
                cnt+=L[que[p]]-L[LCA(que[p-1],que[p])];
            printf("%d\n",cnt);
            j+=qlen[k++]; que[0]=0;
        }
        if(u[i]-j+1<=n) que[++que[0]]=u[i]-j+1;
    }
    while(k<=q){
        sort(que+1,que+1+que[0],CMP);
        for(p=2,cnt=que[0]?L[que[1]]:0;p<=que[0];++p)
        cnt+=L[que[p]]-L[LCA(que[p-1],que[p])];
        printf("%d\n",cnt);
        j+=qlen[k++]; que[0]=0;
    }
}

int main()
{
    //freopen("data.in","r",stdin);
    //freopen("data.out","w",stdout);
//    int size = 256 << 20; // 256MB
//    char *p = (char*)malloc(size) + size;
//    __asm__("movl %0, %%esp\n" :: "r"(p));
    int i,t;
    for(scanf("%d",&t),i=1;i<=t;++i){
        printf("Case #%d:\n",i);
        Init();
        DFS(0);
        Query();
    }
    return 0;
}
