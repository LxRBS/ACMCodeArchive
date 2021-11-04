#include<bits/stdc++.h>
using namespace std;

typedef long long s64;
#define rep(i,l,r) for(int i=l;i<=r;++i)
const int N=4e5+5;
namespace LISAN
{
int q[N],n;    
void init(int n0)
{
    sort(q+1,q+n0+1);
    n=unique(q+1,q+n0+1)-q-1;
}
int Q(int x)
{
    return lower_bound(q+1,q+n+1,x)-q;    
}
};
int l[N],r[N],h[N]; 
namespace SEG
{
struct Node
{
    int se_mn,mn_cnt;
    int mn,mx,hl,hr,sum0,sz;
    s64 sum1;    
    bool upd(int h)
    {
        if(h<=mn)return 1;
        sum0=sz;
        if(h>=mx)
        {
            mn=mx=hl=hr=h;
            sum1=0; 
            se_mn=1e9+5;mn_cnt=1;
            return 1;
        }
        if(h<se_mn)
        {
            sum1-=1LL*(h-mn)*(mn_cnt*2-(hl==mn)-(hr==mn));
            if(hl==mn)hl=h;
            if(hr==mn)hr=h;
            mn=h;
            return 1;
        }
        return 0;
    }
}node[N*4];
int n;
#define cl (k*2)
#define cr (cl+1)
#define mid ((l+r)/2)
void init(int k,int l,int r)
{
    node[k].hl=node[k].hr=node[k].mx=node[k].mn=node[k].sum0=node[k].sum1=0;
    node[k].sz=LISAN::q[r+1]-LISAN::q[l];
    node[k].se_mn=1e9+5;node[k].mn_cnt=1;
    if(l==r)return ;
    init(cl,l,mid);
    init(cr,mid+1,r);
}
void init()
{
    n=LISAN::n-1;
    init(1,1,n);
}
void down(int k)
{
    assert(node[cl].upd(node[k].mn)&&node[cr].upd(node[k].mn));
}
void up(int k)
{
    node[k].sum0=node[cl].sum0+node[cr].sum0;
    node[k].sum1=node[cl].sum1+node[cr].sum1+abs(node[cl].hr-node[cr].hl);
    node[k].hl=node[cl].hl;
    node[k].hr=node[cr].hr;
    node[k].mn=min(node[cl].mn,node[cr].mn);
    node[k].mx=max(node[cl].mx,node[cr].mx);
    node[k].se_mn=min(node[cl].mn==node[k].mn?node[cl].se_mn:node[cl].mn,
                    node[cr].mn==node[k].mn?node[cr].se_mn:node[cr].mn);
    node[k].mn_cnt=node[cl].mn_cnt*(node[cl].mn==node[k].mn)+
                    node[cr].mn_cnt*(node[cr].mn==node[k].mn)-(node[cl].hr==node[k].mn&&node[cr].hl==node[k].mn); 
}
int ql,qr,h;
void dfs(int k,int l,int r)
{
    if(ql<=l&&qr>=r)
    {
        if(node[k].upd(h))return ;
    }
    if(ql>r||qr<l)return ;
    down(k);
    dfs(cl,l,mid);dfs(cr,mid+1,r);
    up(k);
}
void upd(int l,int r,int _h)
{
    ql=l;qr=r;h=_h;
    dfs(1,1,n);
}
};

int main()
{
    int tt;
    cin>>tt;
    while(tt--)
    {
        int n;
        cin>>n;
        rep(i,1,n)
        {
            scanf("%d%d%d",l+i,r+i,h+i);
            LISAN::q[i*2-1]=l[i];LISAN::q[i*2]=r[i];
        }
        LISAN::init(n*2);
        SEG::init();
        rep(i,1,n)
        {
            SEG::upd(LISAN::Q(l[i]),LISAN::Q(r[i])-1,h[i]);
            //cerr<<SEG::node[1].sum0<<" "<<SEG::node[1].sum1<<" "; 
            printf("%lld\n",SEG::node[1].sum0*2+SEG::node[1].sum1+SEG::node[1].hl+SEG::node[1].hr);
        }
    }    
} 