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

const int P=998244353,N=1e6+5;
int k,t,n,T; ll x[N],y[N],fac[N],ans,s;

ll Pow(ll x,ll k) {
    assert(k>=0);
    ll ret=1;
    for (; k; k>>=1,x=x*x%P) if (k&1) ret=ret*x%P;
    return ret;
}

ll Inv(ll x) {
    assert(x>0);
    return Pow(x,P-2);
} 

void Mul(ll &x,ll y){
    x*=y;
    x%=P;
}

ll mul(ll x,ll y) {
    return x*y%P;
}

void Add(ll &x,ll y) {
    x+=y;
    x%=P; 
}

ll add(ll x,ll y) {
    return (x+y)%P;
}

void work() {
    ans=fac[k-1];
    Mul(ans,Pow(t,k-1));
    ll sum=0;
    rep(i,1,k+1) {
        Add(sum,mul(x[i],Inv(Pow(y[i],t))));
        Mul(ans,mul(x[i],Inv(Pow(y[i],t+1))));
    }
    Mul(ans,Inv(Pow(sum,k)));
    Add(ans,P);
}

int main() {
//    file_put();
    
    scanf("%d",&T);
    fac[0]=1;
    rep(i,1,N) fac[i]=fac[i-1]*i%P;
    while (T--) {
        scanf("%d%d",&k,&t),s=0;
        rep(i,1,k+1) scanf("%lld",&x[i]);
        rep(i,1,k+1) scanf("%lld",&y[i]),s+=y[i];
        rep(i,1,k+1) Mul(y[i],Inv(s%P));
        work();
        printf("%lld\n",ans);
    } 
    
    return 0;
}
 