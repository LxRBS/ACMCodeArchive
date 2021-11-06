#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define xx first
#define yy second
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)
#define ld_ll(X) (63-__builtin_clzll(ll(X)))
const ll oo = 0x3f3f3f3f3f3f3f3fLL;

int main() {
	cin.sync_with_stdio(0);

	ll n;
	cin >> n;

	ll jeff;
	cin >> jeff;
	map<ll,ll,greater<ll>> points2ppl;
	FOR(i,1,n) {
		ll p;
		cin >> p;
		points2ppl[p]++;
	}

	ll res = 0;
	while(true) {
		auto lead = points2ppl.begin();
		auto runnerup = lead; runnerup++;
		ll total, step = ld_ll(lead->yy) + 1;
		if(runnerup == points2ppl.end()) {
			total = oo;
		} else {
			total = step * (lead->xx - runnerup->xx);
		}
		if(total != oo && jeff - runnerup->xx >= total) {
			runnerup->yy += lead->yy;
			points2ppl.erase(lead);
			jeff -= total;
			res += total;
		} else {
			ll mi = 0, ma = total;
			while(ma - mi > 1) {
				ll mid = (ma + mi) / 2;
				ll newjeff = jeff - mid;
				ll newlead = lead->xx - mid / step;
				if(newjeff >= newlead) {
					mi = mid;
				} else {
					ma = mid;
				}
			}
			res += mi;
			break;
		}
	}

	cout << res << endl;
}
