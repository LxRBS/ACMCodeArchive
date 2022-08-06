#include <cstdio>
#include <map>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <queue>
#include <stack>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
using namespace std;
#define LL long long
#define pp pair<int,int>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
    const int sz=1<<22;
    char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
    inline char gc(){
        return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
    }
    template<class T> void gi(T& x){
        x=0; int f=1;char c=gc();
        if(c=='-')f=-1;
        for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
        for(;c>='0'&&c<='9';c=gc())
            x=x*10+(c-'0');
        x=x*f;
    }
    inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
    inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
    template<class T> void pi(T x,char c='\n'){
        if(x<0)pc('-'),x=-x;
        if(x==0) pc('0'); int t=0;
        for(;x;x/=10) p[++t]=x%10+'0';
        for(;t;--t) pc(p[t]); pc(c);
    }
    struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=1e9+7;
int add(int x,int y){
    return x+y>=mod?x+y-mod:x+y;
}
int dec(int x,int y){
    return x-y<0?x-y+mod:x-y;
}
int mul(int x,int y){
    return 1ll*x*y%mod;
}
int qkpow(int a,int b){
    if(b<0)return 0;
    int ans=1,base=a%mod;
    while(b){
        if(b&1)ans=1ll*ans*base%mod;
        base=1ll*base*base%mod;
        b>>=1;
    }
    return ans;
}
int fac[1000005],inv[1000005],Invn[1000005];
inline int C(int n,int m){
    if(n<m||m<0)return 0;
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
    inv[0]=1;
    inv[n]=qkpow(fac[n],mod-2);
    for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
const int MAXN=1.4e6+1005;
int T,n,B,iv2,iv6,num[MAXN],prime[MAXN],p[MAXN],cnt,invp[MAXN],mu[MAXN],G[MAXN],f[MAXN];
int *preR[1400005],*preW[1400005];
vector<int>ys[MAXN],ys2[MAXN],ys3[MAXN];
int ans,pregcd[1015][1015];
bool vis[MAXN];
int sq,si,g1[MAXN],g2[MAXN],gp1[MAXN],gp2[MAXN],dp1[MAXN],dp2[MAXN],id1[MAXN],id2[MAXN];
int Id(int p){
    return p<=sq?id1[p]:id2[n/p];
}
void premin25(){
    cnt=si=0;
    sq=sqrt(n*1.0)+10;
    for(int i=1;i<=sq;i++)vis[i]=0;
    for(int i=2;i<=sq;i++){
        if(!vis[i])prime[++cnt]=i,gp1[cnt]=add(gp1[cnt-1],i),gp2[cnt]=dec(gp2[cnt-1],1ll*i*i%mod);
        for(int j=1;j<=cnt&&i*prime[j]<=sq;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }
    }
    for(int i=1;i<=1001000;i++)ys[i].clear(),ys3[i].clear();
    for(int i=1;i<=sqrt(n*1.0)+5;i++)
        if(G[i])
        for(int j=i;j<=1001000;j+=i)
            ys[j].push_back(i);
    for(int i=1;i<=sqrt(n*1.0)+5;i++)
        if(mu[i])
        for(int j=i;j<=1001000;j+=i)
            ys3[j].push_back(i);
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        num[++si]=n/r;
        int x=n/r;
        g1[si]=dec(1ll*(x+1)*x%mod*iv2%mod,1);
        g2[si]=dec(1ll*x*(x+1)%mod*(2*x+1)%mod*iv6%mod,1);
        if(n/r<=sq)id1[n/r]=si;
        else id2[r]=si;
    }
    for(int i=1;i<=cnt;i++){
        int sqr=prime[i]*prime[i];
        for(int j=1;j<=si&&num[j]>=sqr;j++){
            int p=Id(num[j]/prime[i]);
            g1[j]=dec(g1[j],1ll*prime[i]*dec(g1[p],gp1[i-1])%mod);
            g2[j]=dec(g2[j],1ll*prime[i]*prime[i]%mod*add(g2[p],gp2[i-1])%mod);
        }    
    }
    for(int i=1;i<=si;i++)dp1[i]=g1[i],dp2[i]=dec(0,g2[i]);
    for(int i=cnt;i>=1;i--){
        for(int j=1;j<=si&&prime[i]*prime[i]<=num[j];j++){
            int K=1;
            for(LL pkx=prime[i];pkx*prime[i]<=num[j];K++,pkx*=prime[i]){
                dp1[j]=add(dp1[j],1ll*prime[i]*dec(dp1[Id(num[j]/pkx)],gp1[i])%mod);
                dp1[j]=add(dp1[j],prime[i]);
                if(K==1)dp2[j]=dec(dp2[j],1ll*prime[i]*prime[i]%mod*dec(dp2[Id(num[j]/pkx)],gp2[i])%mod);
            }
        }
    } 
    for(int i=1;i<=si;i++)dp1[i]=add(dp1[i],1),dp2[i]=add(dp2[i],1); 
}
void sieve(){
    for(int i=1;i<=1013;i++){
        pregcd[i][i]=i;
        for(int j=i+1;j<=1013;j++)
            pregcd[i][j]=pregcd[j][i]=__gcd(i,j);
    }
    p[1]=1,mu[1]=1,f[1]=1;
    for(int i=2;i<=1400000;i++){
        if(!vis[i])prime[++cnt]=i,p[i]=i,mu[i]=-1,invp[i]=f[i]=qkpow(i,mod-2);
        for(int j=1;i*prime[j]<=1400000;j++){
            vis[i*prime[j]]=1;
            mu[i*prime[j]]=-mu[i];
            p[i*prime[j]]=p[i]*prime[j];
            f[i*prime[j]]=1ll*f[i]*invp[prime[j]]%mod;
            if(i%prime[j]==0){
                p[i*prime[j]]=p[i];
                f[i*prime[j]]=f[i];
                mu[i*prime[j]]=0;
                break;
            }
        }
    }
    for(int T=1;T<=1400000;T++){
        preR[T]=new int[1400000/T+1];
        preW[T]=new int[1400000/T+1];
        memset(preR[T],0,sizeof(int)*(1400000/T+1));
        memset(preW[T],0,sizeof(int)*(1400000/T+1));
        for(int j=1;j<=1400000/T;j++){
            preR[T][j]=add(preR[T][j-1],p[j*T]);
            if(mu[j*T]==-1)preW[T][j]=dec(preW[T][j-1],1ll*p[j*T]*p[j*T]%mod);
            else if(mu[j*T]==1)preW[T][j]=add(preW[T][j-1],1ll*p[j*T]*p[j*T]%mod);
            else preW[T][j]=preW[T][j-1];
        }
    }
    for(int i=1;i<=1001000;i++){
        if(mu[i]==-1)
            for(int j=1;j<=1001000/i;j++)
                G[i*j]=dec(G[i*j],f[j]);
        else if(mu[i])
            for(int j=1;j<=1001000/i;j++)
                G[i*j]=add(G[i*j],f[j]);
    }
    for(int i=1;i<=1013;i++)
        if(G[i])
            for(int j=i;j<=1013;j+=i)
                ys2[j].push_back(i);
}
int lcm(int x,int y){
    return x*y/pregcd[x][y];
}
int W(int N,int T){
    if(N==1){
        if(mu[T]==1)return 1ll*p[T]*p[T]%mod;
        else if(mu[T]==-1)return dec(0,1ll*p[T]*p[T]%mod);
        else return 0;
    }
    if(N<=0)return 0;
    if(T==1)return dp2[Id(N)];
    if(N*T<=1400000)return preW[T][N];
    int tot=0;
    for(auto d:ys3[T]){
        if(mu[d]==-1)tot=dec(tot,W(N/d,d));
        else if(mu[d])tot=add(tot,W(N/d,d));
        if(d>N)break;
    }
    if(mu[T]==-1)return dec(0,1ll*tot*p[T]%mod*p[T]%mod);
    else return 1ll*tot*p[T]%mod*p[T]%mod;
}
int R(int N,int T){
    if(N<=0)return 0;
    if(N==1)return p[T];
    if(T==1)return dp1[Id(N)];
    if(N*T<=1400000)return preR[T][N];
    int tot=0;
    for(auto V:ys[T]){
        if(G[V])tot=add(tot,1ll*G[V]*R(N/V,V)%mod);    
        if(V>N)break;
    }
    return 1ll*tot*p[T]%mod;
}
int F(int N,int x,int y){
    int tot=0;
    for(auto T1:ys2[x])
            for(auto T2:ys2[y])
                if(mu[lcm(T1,T2)])
                    tot=add(tot,1ll*G[T1]*G[T2]%mod*W(N/lcm(T1,T2),lcm(T1,T2))%mod);
    return 1ll*p[x]*p[y]%mod*tot%mod;
} 
void calc1(){
    for(int T=1;T<=B;T++){
        if(mu[T]==-1){
            int fk1=R(n/T,T),fk2=R(n/B,T); 
            ans=dec(ans,dec(1ll*fk1*fk1%mod,1ll*fk2*fk2%mod));
        }
        else if(mu[T]){
            int fk1=R(n/T,T),fk2=R(n/B,T); 
            ans=add(ans,dec(1ll*fk1*fk1%mod,1ll*fk2*fk2%mod));
        }
    }    
}
void calc2(){
    for(int i=1;i<=n/B;i++)
        for(int j=i;j<=n/B;j++){
            if(i==j)ans=add(ans,F(n/max(i,j),i,j));
            else ans=add(ans,2ll*F(n/max(i,j),i,j)%mod);
        }
} 
signed main(){
    iv2=qkpow(2,mod-2),iv6=qkpow(6,mod-2);
    sieve();
    gi(T);
    while(T--){
        ans=0;
        gi(n);
        B=pow(n,0.666),B=max(B,1);
        premin25();
        calc1();
        calc2();
        pi(ans,'\n');     
    }
    return 0;
}
