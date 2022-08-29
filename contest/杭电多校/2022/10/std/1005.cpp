#include <bits/stdc++.h>
using namespace std;
#define fo(i,j,k) for(int i=(j),end_i=(k);i<=end_i;i++)
#define fd(i,j,k) for(int i=(j),end_i=(k);i>=end_i;i--)
#define ll long long
const int N=(1<<20)+1;
int n,m;
ll a[N],b[N];
int c[N],d[N];
ll s1[N<<2],s2[N<<2];
#define lc (u<<1)
#define rc (u<<1|1)
#define ls lc,l,mid
#define rs rc,mid+1,r
inline void add(int u,int l,int r,int x,int d1,ll d2)
{
    s1[u]+=d1; s2[u]+=d2;
    if(l==r) return;
    int mid=l+r>>1;
    return x<=mid?add(ls,x,d1,d2):add(rs,x,d1,d2);
}
ll t1,t2;
inline void ask(int u,int l,int r,int L,int R)
{
    if(L<=l&&r<=R) return (void)(t1+=s1[u],t2+=s2[u]);
    int mid=l+r>>1;
    if(L<=mid) ask(ls,L,R);
    if(mid<R)  ask(rs,L,R);
}
inline int work(int u,int l,int r,ll d)
{
    if(l==r) return l;
    int mid=l+r>>1;
    return d>s1[lc]?work(rs,d-s1[lc]):work(ls,d);
}
int u;
inline void solve()
{
    u=work(1,1,m,(s1[1]+1)>>1);
    t1=t2=0;
    ask(1,1,m,1,u);
    printf("%lld\n",(b[u]*t1-t2+(s2[1]-t2)-b[u]*(s1[1]-t1)));
}

inline void work()
{
    scanf("%d",&n);
    fo(i,1,n)
    {
        scanf("%d",&a[i]); scanf("%d",&c[i]);
        a[i]-=c[i];
        scanf("%d",&c[i]);
    }
    
    a[1]=0;
    fo(i,2,n) a[i]+=a[i-1],b[i]=a[i];
    sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;
    fo(i,1,n) d[i]=lower_bound(b+1,b+m+1,a[i])-b;
    fo(i,1,n) add(1,1,m,d[i],c[i],b[d[i]]*c[i]);
    solve();
    int x,y,q; scanf("%d",&q);
    for(;q--;)
    {
        scanf("%d%d",&x,&y);
        add(1,1,m,d[x],(y-c[x]),b[d[x]]*(y-c[x]));
        c[x]=y; solve();
    }
    fo(i,1,n) a[i]=b[i]=c[i]=d[i]=0;
    fo(i,0,n<<2) s1[i]=s2[i]=0;
}
int main()
{
    int T; scanf("%d",&T);
    while(T--) work();
    return 0;
}