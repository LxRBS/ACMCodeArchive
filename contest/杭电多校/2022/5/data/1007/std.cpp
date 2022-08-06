#include<stdio.h>
#include<vector>
#include<algorithm>
//#include<math.h>
#include<string.h>
#define fr(i,l) for(S i=0;i<l;i++)
#define S int
#define U unsigned
#define UL U long long
#define LL long long
constexpr U mod=998244353u;
constexpr U g=3u;
constexpr U gi=332748118u;
using std::max;
using std::min;
using std::swap;
U pow(U a,U b)
{
    U ans=1;
    while(b)
    {
        if(b&1)ans=(UL)ans*a%mod;
        a=(UL)a*a%mod;
        b>>=1;
    }
    return ans;
}
U mo(U x){return x>=mod?x-mod:x;}
U& mul(U&a,U b){return a=(UL)a*b%mod;}
void mov(U*a,const U*b,S len){memmove(a,b,len*sizeof(U));}

namespace Poly
{
    constexpr S ml=1<<19,mn=80;
    U mem[(ml+16)*mn],*stk[mn],top=mn,f[(ml+16)*2],wr[ml+16],wi[ml+16],ninv[ml+16];
    U*m(){return stk[--top];}void m(U*p){stk[top++]=p;}
    S up(S x){S l=1;while(l<x)l<<=1;return l;}
    void init()
    {
        fr(i,mn)stk[i]=mem+i*(ml+16);
        U*fp;
        for(S len=1;fp=f+len,len<=ml;len<<=1)
            fr(i,len)fp[i]=(fp[i>>1]>>1)|(i&1?len>>1:0);
        for(S len=1;len<ml;len<<=1)
        {
            U Wr=pow(g,(mod-1)/(len<<1));
            U Wi=pow(gi,(mod-1)/(len<<1));
            U tr=1,ti=1;
            fr(i,len)
            {
                wr[len+i]=tr;mul(tr,Wr);
                wi[len+i]=ti;mul(ti,Wi);
            }
        }
    }
#define lst(n,a,x) poly&n(a){x return*this;}
struct poly
{
    U*mem,*a;
    S len;
    poly(S len):len(len){a=mem=m();cls(0,len);}
    poly():poly(1){}
    poly(U x):poly(){a[0]=x;}
    poly(U*l,S len):len(len){a=mem=m();mov(a,l,len);}
    poly(const poly&b):poly(b.a,b.len){}
    ~poly(){if(mem)m(mem);}
    lst(operator=,const poly&b,if(mem)rsz(b.len);mov(a,b.a,b.len);)
    U& operator[](S idx){return a[idx];}
    poly& cls(S l,S len){memset(a+l,0,len*4);return *this;}
    lst(rsz,S nlen,if(nlen>len)cls(len,nlen-len);len=nlen;)
    template<U*wp=wr>
    lst(NTT,S len=-1,static UL a[ml+16];
        if(~len)rsz(len);else len=this->len;
        fr(i,len)a[i]=this->a[f[len+i]];
        for(S i=1;i<len;i<<=1)
        {
            U*w=wp+i;
            for(S j=0;j<len;j+=i<<1)
            fr(k,i)
            {
                UL x=a[j+k];
                UL y=a[i+j+k]*w[k]%mod;
                a[j+k]=x+y;
                a[i+j+k]=x-y+mod;
            }
        }
        fr(i,len)this->a[i]=a[i]%mod;
    )
    lst(NTTi,S len=-1,NTT<wi>(len);*this*=pow(this->len,mod-2);)
    poly operator+(const poly&b){return poly(*this)+=b;}
    poly operator-(const poly&b){return poly(*this)-=b;}
    poly operator*(const poly&b){return poly(*this)*=b;}
    poly operator*(U x){return poly(*this)*=x;}
    lst(operator+=,const poly&b,rsz(max(len,b.len));fr(i,b.len)a[i]=mo(a[i]+b.a[i]);)
    lst(operator-=,const poly&b,rsz(max(len,b.len));fr(i,b.len)a[i]=mo(a[i]-b.a[i]+mod);)
    lst(operator*=,poly b,S l=up(len+b.len-1);NTT(l).vmul(b.NTT(l)).NTTi();)
    lst(operator*=,U x,fr(i,len)mul(a[i],x);)
    lst(vmul,const poly&b,fr(i,len)mul(a[i],b.a[i]);)
    lst(print,,fr(i,len)printf("%u ",a[i]);puts("");)

};
};
using Poly::poly;

U fact[500001];
U ifact[500001];

U C(int n,int m)
{
    if(m<0||m>n)return 0;
    return (UL)fact[n]*ifact[m]%mod*ifact[n-m]%mod;
}
int p[500000];
int vis[500000];
int sz[500000],num;

poly calc(int l,int r)
{
    if(l==r)
    {
        poly t(sz[l]/2+1);
        t[0]=1;
        for(S i=1;i<t.len;i++)
            t[i]=mo(C(sz[l]-i-1,i-1)+C(sz[l]-i,i));
        return t;
    }
    else
    {
        int mid=l+r>>1;
        poly a=calc(l,mid);
        poly b=calc(mid+1,r);
        int len=a.len+b.len-1;
        return (a*=b).rsz(len);
    }
}



void sol()
{
    int n,k;
    scanf("%d%d",&n,&k);
    fr(i,n)scanf("%d",p+i),p[i]--;
    memset(vis,0,4*n);
    num=0;
    fr(i,n)
    {
        if(!vis[i])
        {
            vis[i]=1;
            sz[num]=1;
            int t=p[i];
            while(!vis[t])
            {
                vis[t]=1;
                sz[num]++;
                t=p[t];
            }
            if(sz[num]>1)num++;
        }
    }
    poly a=calc(0,num-1);
    U ans=k>=a.len?0:a[k];
    printf("%u\n",ans);
}

int main()
{
    Poly::init();
    fact[0]=1;
    for(S i=1;i<=500000;i++)
        fact[i]=(UL)fact[i-1]*i%mod;
    ifact[500000]=pow(fact[500000],mod-2);
    for(S i=500000;i;i--)
        ifact[i-1]=(UL)ifact[i]*i%mod;
    int T;
    scanf("%d",&T);
    while(T--)sol();
}