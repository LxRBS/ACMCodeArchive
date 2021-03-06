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
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n) rep(j,0,m) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
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
const int N=(1<<20)+5; 
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

int n,m,a[N],p[N],p2[N],x,T;
ll ans=0;

ll Pow(ll x,ll k) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%_p) if (k&1) ret=ret*x%_p;
    return ret;
} 

void FWT(int a[],int n){
    for(int d=1; d<n; d<<=1)  
        for(int m=d<<1,i=0; i<n; i+=m)  
            for(int j=0; j<d; j++){  
                int x=a[i+j],y=a[i+j+d];  
                a[i+j]=x+y; 
            }
}

int main() {
//    file_put();
    
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&m);
        mem(a,0);
        rep(i,1,m+1) scanf("%d",&x),a[x]++;
        int SS=1<<n;
        memcpy(p,a,SS*sizeof(int));
        FWT(p,SS);
        memcpy(p2,p,SS*sizeof(int));
        FWT(p2,SS);
        
        ans=0;
        rep(S,0,SS) {
            ll ret=1<<(__builtin_popcount(S));
            ret=ret*Pow(p[S],_p-2)%_p;
            ret=ret*p2[S]%_p;
            ans+=ret;
            ans%=_p;
        }
        printf("%lld\n",ans);
    }
    
    return 0;
}
 