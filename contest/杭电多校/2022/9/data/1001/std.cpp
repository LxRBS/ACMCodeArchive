// #pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("O3")
#pragma GCC optimize("O2")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
// #pragma GCC optimize("trapv")
#include<bits/stdc++.h>
// #include <bits/extc++.h>
#define int long long
#define double long double
// #define i128 long long
// #define double long double
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
 
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
const int mod=998244353;
const double EPS=1e-9;
const double pi=acos(-1);
const int INF=1e18;
const int N=5007;
mt19937 rng(1235);
int n;
vi ans;
void solve(vi &x){
    vector<pair<int,int>> y;
    int n=sz(x);
    for (int i=0;i<n;++i){
        y.push_back({0,x[i]});
        for (int j=0;j<30;++j){
            if (x[i]>>j&1) y[i].first|=(1ll<<(29-j));
        }
    }
    sort(range(y));
    for (int i=0;i<n;++i) ans.push_back(y[i].second);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout.precision(15);
    int _;
    cin>>_;
    while (_--){
	    cin>>n;
	    vi a(n,0);
	    rep(i,n) cin>>a[i];
	    map<int,int> cnt;
	    ans.clear();
	    rep(i,n){
		    cnt[a[i]]++;
		    if (cnt[a[i]]>2){cout<<"NO\n"; goto cont;} 
	    }
	    cout<<"YES\n";
	    solve(a);
	    for (auto c:ans) cout<<c<<" ";
	    cout<<"\n";
	    cont:;
    }
	return 0;
}
/*

*/