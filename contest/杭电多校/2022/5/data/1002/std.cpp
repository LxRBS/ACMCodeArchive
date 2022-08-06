#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define de(x) cout << #x <<" = "<<x<<endl
#define dd(x) cout << #x <<" = "<<x<<" "
const ll P=29ll<<57|1;
const int Lim=1e6, MAXN=Lim+10; 
int fc[MAXN], prime[MAXN/10], cntprime;
ll inv[64];
inline ll mul(ll a,ll b,ll p=P) { return (a*b-(ull)((long double)a/p*b)*p+p)%p; }
inline ll kpow(ll a, ll x) { ll ans=1; for(;x;x>>=1, a=mul(a, a)) if(x&1) ans=mul(ans, a); return ans; }
inline ll h(ll p, int k, ll pk) {
	return P-mul(pk, mul(inv[k], inv[k-1]));
}
inline ll PN_sieve(const ll n, const int flr, const ll hd) {
	ll res=mul(mul(n, mul(n+1, inv[2])), hd);
	for(int i=flr+1; i<=cntprime; ++i) {
		int p=prime[i], k=1;
		ll val=n/p, pk=p;
		if(val<p)
			break;
		while(val>=p) {
			val/=p;
			pk*=p;
			++k;
			
			res+=PN_sieve(val, i, mul(hd, h(p, k, pk)));
			if(res>=P)
				res-=P;
		}
	}
	return res;
}
inline void sieve() {
	for(int i=2; i<=Lim; ++i) {
		if(!fc[i]) fc[i]=prime[++cntprime]=i;
		for(int j=1; j<=cntprime; ++j)
			if(prime[j]>fc[i]||prime[j]*i>Lim)
				break;
			else
				fc[prime[j]*i]=prime[j];
	}
}
inline void init() {
	sieve();
	for(int i=1; i<64; ++i)
		inv[i]=kpow(i, P-2);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	init();
	int T; cin>>T;
	ll M;
	while(T--) {
		cin>>M;
		cout<<mul(PN_sieve(M, 0, 1), kpow(M, P-2))<<"\n";
	}
	cout.flush();
	return 0;
}
