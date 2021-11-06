# include <iostream>
# include <sstream>
# include <cstdio>
# include <cstdlib>
# include <algorithm>
# include <string>
# include <cstring>
# include <cmath>
# include <stack>
# include <queue>
# include <vector>
# include <list>
# include <map>
# include <set>
# include <deque>
# include <iterator>
# include <functional>
# include <bitset>
# include <climits>
# include <ctime>
# include <assert.h>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define odd(x) ((x)&1)
#define sqr(x) ((x)*(x))
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
#define all(x) (x).begin(),(x).end()
#define mem(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for (int i=(a); i<(b); ++i)
#define per(i,a,b) for (int i=(b)-1; i>=1; --i)
#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
const int oo = /*2 * 1000 * 1000 * 1000*/0x3f3f3f3f;
const ll ooo=9223372036854775807ll; 
const int _cnt = 1000 * 1000 + 7;
const int _p = 998244353;
const int N=505; 
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

ll Pow(ll x,ll k) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%_p) if (k&1) ret=ret*x%_p;
    return ret;
}

struct Matrix{
    static const int N=511,P=998244353;
    int n,a[N][2*N]; bool t;
    
    void In(ll a[][::N],int n) {
        this->n=n;
        rep(i,1,n+1) rep(j,1,n+1) this->a[i][j]=a[i][j], this->a[i][n+j]=0;
        rep(i,1,n+1) this->a[i][i+n]=1;
    }
    
    void Out(ll b[][::N]) {
        rep(i,1,n+1) rep(j,1,n+1) b[i][j]=a[i][n+j];
    }
    
    void Print() {
        if (t) printf("Inv Is:\n"); else { printf("Not Invertable!\n"); return; }
        rep(i,1,n+1) rep(j,1,n+1) printf("%d%c",a[i][n+j]," \n"[j==n]);
    }
    
    bool getinv(){
        rep(i,1,n+1){
            if(a[i][i]==0){
                rep(j,i,n+1) if(a[j][i]) swap(a[i],a[j]);
                if(!a[i][i]) return 0;
            }
            int s=a[i][i];
            rep(j,1,n+n+1) a[i][j]=1ll*a[i][j]*Pow(s,P-2)%P;
            rep(j,1,n+1) {
                if(i==j) continue;
                s=1ll*a[j][i]*Pow(a[i][i],P-2)%P;
                rep(k,1,n+n+1) a[j][k]=(a[j][k]-1ll*a[i][k]*s)%P;
            }
        }
        rep(i,1,n+1) rep(j,1,n+n+1) a[i][n+j]=(a[i][n+j]+P)%P;
        return 1;
    }
    
    bool Solve(ll a[][::N],int n,ll b[][::N]) {
        In(a,n),t=getinv(),Out(b); return t;
    }
    
    bool Check(ll a[][::N],ll b[][::N],int n) {
        static int c[::N][::N];
        memset(c,0,sizeof(c));
        rep(i,1,n+1) rep(k,1,n+1) if (a[i][k]) 
            rep(j,1,n+1) if (b[k][j]) c[i][j]+=a[i][k]*b[k][j]%P,c[i][j]%=P;
        rep(i,1,n+1) rep(j,1,n+1) c[i][j]=(c[i][j]+P)%P;
        rep(i,1,n+1) rep(j,1,n+1) if (c[i][j]!=(i==j)) return 0;
        return 1;
    }
}; 


int n;
ll w[N][N],d[N],lambda[N]; 
Matrix M;

int a[N][N],b[N][N];

void solve() {
//    file_put();
    
    scanf("%d",&n);
    rep(i,1,n+1)
        d[i]=0;
    rep(i,1,n+1) rep(j,1,n+1) {
        scanf("%lld",&w[i][j]);
        if (i==j) {
            //if (w[i][j]<=0) return 0*printf("-1\n");
//            lambda[i]=Pow(w[i][i],_p-2);
            lambda[i]=w[i][i];
        }
        d[i]+=w[i][j],d[i]%=_p,w[i][j]=-w[i][j];
    }
    rep(i,1,n+1) w[i][i]=d[i];
//    rep(i,1,n+1) rep(j,1,n+1) w[i][j]*=lambda[i],w[i][j]%=_p;

//    debug_arr2(w,n,n);
    assert(M.Solve(w,n,w));
//    debug_arr2(w,n,n);
//    debug_arr(lambda,n);
    rep(i,1,n+1) rep(j,1,n+1) w[i][j]*=lambda[j],w[i][j]%=_p;
    
    rep(i,1,n+1) rep(j,1,n+1) printf("%lld%c",w[i][j]," \n"[j==n]);
    
    
//    debug_arr2(w,n,n);
    
//    ll p=0;
//    rep(i,1,n+1)
//        rep(j,1,n+1) p^=(w[i][j]+_p)%_p;
//    printf("%lld\n",p);

//    scanf("%d",&n);
//    rep(i,1,n+1) rep(j,1,n+1) scanf("%d",&a[i][j]);
//    M.Solve(a,n,b);
//    M.Print();
//    debug_arr2(a,n,n);
//    debug_arr2(b,n,n);
//    debug(M.t);
//    if (M.Check(a,b,n)) printf("Yes\n"); else printf("No\n");
    
    
    return ;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--)
        solve();
    return 0;
}
 