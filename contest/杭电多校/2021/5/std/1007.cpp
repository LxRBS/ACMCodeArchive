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

const int P=1e9+7;
ll n,ret1,ret2,ret3,q;
int T;

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

ll Pow(ll x,ll k) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%P) if (k&1) ret=ret*x%P;
    return ret;
}

int main() {
    //file_put();
    
    
    scanf("%d",&T);
    
    while (T--) {
        scanf("%lld",&n),n%=P,q=Pow(24,P-2);
    
    
        //ret1=n*n%P*n%P*(n+1)%P*(n+1)%P*(n+1)%P*(1+2*n)%P*q%P;
        ret1=n*n%P*(n+1)%P*(n+1)%P*(1+2*n)%P*Pow(12,P-2)%P*n%P*n%P;
        
        
        
        //ret2=n*(n+1)%P*(n*n%P+n-2)%P*((n*n%P+3*n+2)%P)%P*q%P;
        ret2=(-2 + n + n*n%P)%P*(((-6 + 2*n%P)%P + 3*n*n%P)%P + n*n%P*n%P)%P*Pow(6,P-2)%P;
        ret3=n*(n+1)%P*(2*n+1)%P*Pow(12,P-2)%P*n%P*(n+1)%P;
        printf("%lld\n",((ret3+ret2)%P+P)%P);
        printf("%lld\n",ret1);
        
        
    }
    

    return 0;
}
 
