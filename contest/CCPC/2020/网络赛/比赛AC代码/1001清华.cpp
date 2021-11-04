#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

typedef long long ll;

int read() {
    char ch;
    for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
    int x=ch-'0';
    for(ch=getchar();ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
    return x;
}

const int N=5e5+5,inf=1e9;

int n,m,l[N],r[N],h[N],p[N],f[N],an[N],fir[N],ans;

int get(int x) {return f[x]==x?x:f[x]=get(f[x]);}

void merge(int l,int r) {
    int x=get(l);if (!fir[x]) fir[x]=1,ans+=p[x+1]-p[x];
    for(int y=get(x+1);y<=r;x=y,y=get(x+1)) {
        if (!fir[y]) fir[y]=1,ans+=p[y+1]-p[y];
        f[x]=y;
    }
}

struct Seg{int mn,smn,ls,rs,cnt,cmx;ll sum;}tr[N<<2];

void upd(int v) {
    int ls=v<<1,rs=v<<1|1,x=tr[ls].rs,y=tr[rs].ls;
    if (tr[ls].mn==tr[rs].mn) {
        tr[v].smn=min(tr[ls].smn,tr[rs].smn);
        tr[v].cnt=tr[ls].cnt+tr[rs].cnt;
        tr[v].mn=tr[ls].mn;
    } else if (tr[ls].mn<tr[rs].mn) {
        tr[v].smn=min(tr[ls].smn,tr[rs].mn);
        tr[v].cnt=tr[ls].cnt;
        tr[v].mn=tr[ls].mn;
    } else {
        tr[v].smn=min(tr[ls].mn,tr[rs].smn);
        tr[v].cnt=tr[rs].cnt;
        tr[v].mn=tr[rs].mn;
    }
    tr[v].sum=tr[ls].sum+tr[rs].sum+abs(x-y);
    tr[v].cnt+=((x==tr[v].mn)^(y==tr[v].mn));
    tr[v].ls=tr[ls].ls;tr[v].rs=tr[rs].rs;
}

void build(int v,int l,int r) {
    tr[v].cmx=0;
    if (l==r) {
        tr[v].mn=tr[v].ls=tr[v].rs=tr[v].cnt=tr[v].sum=0;
        tr[v].smn=inf;
        return;
    }
    int mid=l+r>>1;
    build(v<<1,l,mid);build(v<<1|1,mid+1,r);
    upd(v);
}

bool get_Max(int v,int l,int r,int x) {
    if (tr[v].mn>=x) return 1;
    if (tr[v].smn>x) {
        tr[v].sum-=(ll)tr[v].cnt*(x-tr[v].mn);tr[v].mn=x;
        tr[v].ls=max(tr[v].ls,x);tr[v].rs=max(tr[v].rs,x);
        tr[v].cmx=max(tr[v].cmx,x);
        return 1;
    }
    return 0;
} 

void down(int v,int l,int r) {
    if (l==r) return;
    int mid=l+r>>1;
    if (tr[v].cmx) {
        get_Max(v<<1,l,mid,tr[v].cmx);
        get_Max(v<<1|1,mid+1,r,tr[v].cmx);
        tr[v].cmx=0;
    }
}

void get_max(int v,int l,int r,int x,int y,int z) {
    if (x<=l&&r<=y&&get_Max(v,l,r,z)) return;
    down(v,l,r);
    int mid=l+r>>1;
    if (x<=mid) get_max(v<<1,l,mid,x,y,z);
    if (y>mid) get_max(v<<1|1,mid+1,r,x,y,z);
    upd(v);
}

void solve() {
    n=read();
    fo(i,1,n) l[i]=read(),r[i]=read(),h[i]=read(),p[(i<<1)-1]=l[i],p[i<<1]=r[i];
    sort(p+1,p+(n<<1)+1);m=unique(p+1,p+(n<<1)+1)-p-1;
    fo(i,1,n) l[i]=lower_bound(p+1,p+m+1,l[i])-p,r[i]=lower_bound(p+1,p+m+1,r[i])-p-1;
    fo(i,1,m) f[i]=i,fir[i]=0;ans=0;
    fo(i,1,n) {
        merge(l[i],r[i]);
        an[i]=ans<<1;
    }
    build(1,0,m);
    fo(i,1,n) {
        get_max(1,0,m,l[i],r[i],h[i]);
        printf("%lld\n",tr[1].sum+an[i]);
    }
}

int main() {
    for(int ty=read();ty;ty--) solve();
    return 0;
}