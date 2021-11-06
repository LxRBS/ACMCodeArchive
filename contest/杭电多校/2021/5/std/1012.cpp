#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
} 

const int P=998244353;

const int _N=300005; ll inv[_N<<2],fac[_N<<2],fac_inv[_N<<2];
inline ll add(ll x,ll y) { x+=y; return x%P; }
inline ll mul(ll x,ll y) { return (ll)x*y%P; }
inline ll Pow(ll x,ll k) { ll ans=1; for (;k;k>>=1,x=x*x%P) if (k&1) (ans*=x)%=P; return ans; } 
inline void init_inv(int n) { inv[1]=1; rep(i,2,n+1) inv[i]=mul(P-P/i,inv[P%i]); }
inline void init_fac(int n) { 
    fac[0]=fac_inv[0]=1; 
    rep(i,1,n+1) fac[i]=mul(fac[i-1],i),fac_inv[i]=mul(fac_inv[i-1],inv[i]); 
}

template <class V>
struct FT{
    int n,nn; V w[2][_N<<2],rev[_N<<2],tmp;
    inline int init_len(int _n) { for (n=1; n<=_n; n<<=1); return n; }
    inline int Init(int _n) {
        init_len(_n); if (n==nn) return n; nn=n;
        V w0=Pow(3,(P-1)/n); w[0][0]=w[1][0]=1;
        rep(i,1,n) w[0][i]=w[1][n-i]=mul(w[0][i-1],w0);
        rep(i,0,n) rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1)); return n;
    }
    void FFT(V A[],int op){
        rep(i,0,n) if (i<rev[i]) swap(A[i],A[rev[i]]);
        for (int i=1; i<n; i<<=1)
            for (int j=0,t=n/(i<<1); j<n; j+=i<<1)
                for (int k=j,l=0; k<j+i; k++,l+=t) {
                    V x=A[k],y=mul(w[op][l],A[k+i]);
                    A[k]=add(x,y),A[k+i]=add(x-y,P);
                }
        if (op) { tmp=inv[n]; rep(i,0,n) A[i]=mul(A[i],tmp); }
    }
};

template <class V>
struct Calculator{
    FT<V> T; V X[_N<<2],Y[_N<<2],A[_N<<2],B[_N<<2],C[_N<<2];
    inline void Fill(V a[],V b[],int n,int len) {
        if (a!=b) memcpy(a,b,sizeof(V)*n); fill(a+n,a+len,0);
    }
    inline void Add(V a[],int n,V b[],int m,V c[],int t=1) {
        n=max(n,m); rep(i,0,n) c[i]=add(a[i],t*b[i]);
    }
    inline void Dot_Mul(V a[],V b[],int len,V c[]) {
        rep(i,0,len) c[i]=mul(a[i],b[i]);
    }
    inline void Dot_Mul(V a[],int len,V v,V c[]) {
        rep(i,0,len) c[i]=mul(a[i],v);
    }
    inline void Mul(V a[],int n,V b[],int m,V c[]) {
        int len=T.Init(n+m-1); Fill(X,a,n,len),Fill(Y,b,m,len);
        T.FFT(X,0),T.FFT(Y,0),Dot_Mul(X,Y,len,c),T.FFT(c,1);
    }
    inline void Int(V a[],int n,V b[]) {
        per(i,0,n) b[i+1]=mul(a[i],inv[i+1]); b[0]=0;
    }
    inline void Der(V a[],int n,V b[]) {
        rep(i,1,n) b[i-1]=mul(a[i],i); b[n-1]=0;
    }
    inline void Inv(V a[],int n,V b[]) {
        if (n==1) { b[0]=Pow(a[0],P-2),b[1]=0; return; }
        Inv(a,(n+1)>>1,b); int len=T.Init(2*n-1);
        Fill(X,a,n,len),Fill(b,b,n,len),T.FFT(X,0),T.FFT(b,0);
        rep(i,0,len) b[i]=mul(b[i],2-mul(b[i],X[i]));
        T.FFT(b,1),Fill(b,b,n,len);
    }
    inline void Log(V a[],int n,V b[]) {
        static V A[_N<<2],B[_N<<2]; 
        Der(a,n,A),Inv(a,n,B),Mul(A,n,B,n,b);
        Int(b,n,b),Fill(b,b,n,T.n);
    }
    inline void Exp(V a[],int n,V b[]) {
        if (n==1) { b[0]=exp(a[0]),b[1]=0; return; }
        Exp(a,(n+1)>>1,A),Log(A,n,B),Add(a,n,B,n,B,-1);
        (B[0]+=1)%=P,Mul(A,n,B,n,b),Fill(b,b,n,T.n);
    }
    inline void Power(V a[],int n,ll k,V b[]) {
        Log(a,n,C),Dot_Mul(C,n,k,C),Exp(C,n,b),Fill(b,b,n,T.n);
    }
    inline void Dirichlet_Mul(V a[],int n,V b[],int m,V c[],int L) {
        int len=min((ll)n*m,(ll)L); Fill(c,c,0,L+1);
        rep(i,1,n+1) for (int j=1; j<=m && (ll)i*j<=len; j++) 
            c[i*j]=add(c[i*j],mul(a[i],b[j]));
    }
};



ll C(ll n, ll m){
    if (n<0 || m<0 || n<m) return 0;
    return fac[n]*fac_inv[m]%P*fac_inv[n-m]%P;
}

ll POW(ll x, ll k){
    ll ret=1;
    for (;k;k>>=1,x=x*x%P) if (k&1) ret=ret*x%P;
    return ret;
}

ll POW(ll x, ll k, ll P){
    ll ret=1;
    for (;k;k>>=1,x=x*x%P) if (k&1) ret=ret*x%P;
    return ret;
}

ll a[_N<<2],b[_N<<2],c[_N<<2],s=0;
int n,m,k,_T;
Calculator<ll> T;

int main() {
    //file_put();
    
    init_inv(800005);
    init_fac(800005);
    
    scanf("%d",&_T);
    while (_T--) {
        scanf("%d%d",&n,&m);
        rep(k,0,m+1) a[k]=C(k+n-1,n-1), s=(s+a[k])%P; 
        s=POW(m+1,n);
        //debug_arr(a,20);
        T.Dirichlet_Mul(a,m,a,m,b,m);
        b[0]=2*s-1;
        T.Dot_Mul(b,m+1,POW(2*s-1,P-2),b);
        T.Power(b,m+1,POW(n,m),c);
        //T.Power(b,m+1,n,c);
        T.Dot_Mul(c,m+1,POW(2*s-1,POW(n,m,P-1)),c);
        rep(k,0,m+1) printf("%lld\n",(c[k]+P)%P);
    }
    
    return 0;
}
 