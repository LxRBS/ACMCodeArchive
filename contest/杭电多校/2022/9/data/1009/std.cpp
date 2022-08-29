// #pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
// #pragma GCC optimize("trapv")
#include<bits/stdc++.h>
 
#define int long long
#define double long double
using namespace std;
 
#define rep(i,n) for (int i=0;i<(int)(n);++i)
#define rep1(i,n) for (int i=1;i<=(int)(n);++i)
#define range(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
 
typedef long long ll;
typedef unsigned long long ull;
// typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
int dx[]={0,1,0,-1,1,-1};
int dy[]={1,0,-1,0,1,-1};
const int mod=998244353;
const int INF=LLONG_MAX/4;
const double EPS=1e-9;
const int N=1000007;
const int K=31;
 
mt19937 rng(1234);

int n,l,r,x;
signed main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cout.precision(15), cerr.precision(15);
    int _;
    cin>>_;
    while (_--){
        cin>>n>>l>>r>>x;
        int m=min(n,K);
        if ((n-m)&1) x^=r;
        bool diff=0;
        int sum=0;
        int ans=-1;
        vector<vi> dp(m+1,vi(m+1,-INF)); // i prefix =R, j prefix = L;
        for (int i=30;i>-1;--i){
            if (!diff){
                if ((l>>i&1)^(r>>i&1)){
                    diff=1;
                    for (int j=0;j<=m;++j){
                        if ((j&1)^(x>>i&1)^1) dp[j][m-j]=sum+(1ll<<i)*j;
                    }
                }
                else{
                    if (l>>i&1) sum+=(1ll<<i)*m;
                    int bt=(l>>i&1)*m;
                    if ((bt&1)^(x>>i&1)){
                        cout<<"-1\n";
                        goto cont;
                    }
                }
                // cerr<<"sum: "<<i<<" "<<sum<<endl;
            }
            else{
                vector<vi> f(m+1,vi(m+1,-INF));
                for (int j=0;j<=m;++j){
                    for (int k=0;k+j<=m;++k){
                        for (int c=0;c<=m;++c){
                            if ((c&1)^(x>>i&1)) continue;
                            if (c>m-j&&((r>>i&1)^1)) continue;
                            if (m-c>m-k&&((l>>i&1))) continue;
                            f[(r>>i&1)?max(0ll,j-(m-c)):j][(l>>i&1)?k:max(0ll,k-c)]=max(f[(r>>i&1)?max(0ll,j-(m-c)):j][(l>>i&1)?k:max(0ll,k-c)],dp[j][k]+(1ll<<i)*c);
                        }
                    }
                }
                dp=f;
            }
        }
        if (diff){
            for (int i=0;i<=m;++i) for (int j=0;j<=m;++j) ans=max(ans,dp[i][j]);
            if (ans<0) cout<<ans<<"\n";
            else cout<<ans+(n-m)*r<<"\n";
        }
        else{
            cout<<sum+(n-m)*r<<"\n";
        }
        cont:;
    }
    return 0;
}
/*
1
5 5 9 11
*/