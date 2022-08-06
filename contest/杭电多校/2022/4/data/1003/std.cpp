#include<bits/stdc++.h>
using namespace std;
const int maxne = 600001;
const int maxnn = 100001;
const long long int inf = 1e18;
int n,k;
int e,s,t,cnt;
int last[maxne],q[maxne],check[maxnn];
long long dis[maxnn];
bool is[maxnn],fuhuan;
struct line {int to,next,v;}l[maxne];
void add(int u,int v,int w) { l[++cnt].to=v; l[cnt].next=last[u]; last[u]=cnt; l[cnt].v=w; /*printf("u:%d v:%d w:%d\n",u,v,w);*/}
void spfa(int a,int maxnode)
{
    for(int i=1;i<=maxnode;i++) {dis[i]=inf; check[i]=is[i]=0;}
    dis[a]=0; is[a]=1; q[0]=a; check[a]++; fuhuan=0;
    int head=0,tail=1;
    while(head!=tail)
    {
        int now=q[head++];
        if(head==maxnode+1) head=0;
        for(int i=last[now];i;i=l[i].next)
        {
            if( dis[now]+l[i].v<dis[l[i].to] && dis[now]!=inf)
            {
                dis[l[i].to]=dis[now]+l[i].v;
                if(!is[l[i].to])
                {
                    is[l[i].to]=1;
                    if(dis[l[i].to]<dis[q[head]])
                    {
                        head--; if(head==-1) head=n;
                        q[head]=l[i].to;
                        check[l[i].to]++;
                        if(check[l[i].to]==maxnode) { fuhuan=1; return;}
                    }
                    else
                    {
                        q[tail++]=l[i].to;
                        if(check[l[i].to]==maxnode) { fuhuan=1; return;}
                        if(tail==maxnode+1) tail=0;
                    }
                }
            }
        }
        is[now]=0;
    } 
}
void clear(int x)
{
    cnt=0;
    for(int i=0;i<=x;i++)
    {
        last[i]=q[i]=0;
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int p,q;
        scanf("%d%d",&n,&k);
        //x[j]-x[i]>=k  ==> x[i]-x[j]<=-k 
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&p);
            int st=(i-k>=1)?(i-k):n+1;
            int ed=(i+k-1<=n)?(i+k-1):n;
            add(ed, st, -1*p);
        }    
        for(int i=1;i<=n;i++)
            add(i, (i-1==0?n+1:i-1), 0);
        scanf("%d",&q);
        for(int i=1;i<=q;i++)
        {
            int x,y;
            scanf("%d%d%d",&x,&y,&p);
            add((x!=1)?(x-1):n+1, y, p);
        }
        spfa(n,n+1);
        int tmp = dis[n+1];
        printf("%d\n",fuhuan?-1:-1*tmp);
        clear(n+2);
    }
    return 0;
} 
