#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
mt19937 mrand(random_device{}()); 
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=1010000;
int vis[N],f[N];
int n,T;
int main(int argc, char* argv[]) {
	ifstream input("input");
    ifstream output("output");
    ifstream pout("user_output");
    input>>T;
    for (int i=0;i<T;i++) {
    	input>>n;
    	int x;
    	output>>x;
    	pout>>f[0];
    	for (int i=1;i<n;i++) vis[i]=0;
    	if (x==-1) {
    		if (f[0]!=-1) return 1;
    		continue;
    	}
    	if (f[0]==-1) return 1;
    	for (int i=1;i<n-1;i++) {
    		output>>x;
    		pout>>f[i];
    	}
    	rep(i,0,n-1)  {
    		if (f[i]<1||f[i]>=n) return 1;
    		if (vis[f[i]]) return 1;
    		vis[f[i]]=1;
    	}
    	rep(i,1,n-1) {
    		if (f[i]!=f[i-1]*2%n&&f[i]!=f[i-1]*3%n) return 1;
    	}
    }
    return 0;

}