	
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair <int,int> Pii;
#define reg register
#define mp make_pair
#define pb push_back
#define Mod1(x) ((x>=Phi)&&(x-=Phi))
#define Mod2(x) ((x<0)&&(x+=Phi))
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
template <class T> inline void cmin(T &a,T b){ ((a>b)&&(a=b)); }
template <class T> inline void cmax(T &a,T b){ ((a<b)&&(a=b)); }

char IO;
template <class T=int> T rd(){
    T s=0; int f=0;
    while(!isdigit(IO=getchar())) f|=IO=='-';
    do s=(s<<1)+(s<<3)+(IO^'0');
    while(isdigit(IO=getchar()));
    return f?-s:s;
}

const int N=8e4+10,M=1e7+30;

int n,m;
ll P,Phi;
int notpri[M+1],pri[M/5],pc;
ll A[N],C[N][40];
ull uC[N][40];

ll Calc(ll n){
    ll p=n;
    for(int i=1;1ll*pri[i]*pri[i]<=n;++i) if(n%pri[i]==0) {
        p=p/pri[i]*(pri[i]-1);
        while(n%pri[i]==0) n/=pri[i];
    }
    if(n>1) p=p/n*(n-1);
    return p;
}

ll Mul(ll x,ll y){ return (__int128)x*y%P; }
ll qpow(ll x,ll k) {
    ll res=1;
    for(;k;k>>=1,x=Mul(x,x)) if(k&1) res=Mul(res,x);
    return res;
}

int main(){
    rep(i,0,4e4) rep(j,*uC[i]=1,min(i,30)) uC[i][j]=uC[i-1][j]+uC[i-1][j-1];
    rep(i,2,M) {
        if(!notpri[i]) pri[++pc]=i;
        for(int j=1;j<=pc && 1ll*i*pri[j]<=M;++j) {
            notpri[i*pri[j]]=1;
            if(i%pri[j]==0) break;
        }
    }
    //cout<<pc<<endl;
    //freopen("data04.in","r",stdin);
    int cnt=0;
    rep(_,1,rd()) {
        n=rd(),m=rd(),P=rd<ll>(),Phi=Calc(P);
        //cout<<P<<' '<<Phi<<endl;
        rep(i,0,N-1) A[i]=0;
        rep(i,1,n) A[rd()]++;
        rep(i,0,n) rep(j,*C[i]=1,min(i,m)) C[i][j]=C[i-1][j]+C[i-1][j-1],Mod1(C[i][j]);
        ll ans=1;
        rep(i,2,N-1) if(!notpri[i]) {
            ll res=0;
            ull res2=0;
            for(int x=i;x<N;x*=i) {
                int c=0;
                for(int j=x;j<N;j+=x) c+=A[j];
                if(c<m) break;
                cnt++;
                res+=C[c][m],res2+=uC[c][m],Mod1(res);
            }
            if(res!=(ll)res2 || res>=Phi) res+=Phi;
            if(res) ans=Mul(ans,qpow(i,res));
        }
        printf("%lld\n",ans);
    }
}
