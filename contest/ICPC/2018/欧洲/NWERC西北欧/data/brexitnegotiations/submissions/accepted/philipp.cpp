#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll,ll>;
#define pb push_back
#define xx first
#define yy second
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)
#define FORD(i,a,b) for(ll i = ll(b)-1; i >= (a); i--)

int main() {
	cin.sync_with_stdio(0);

	ll n;
	cin >> n;
	vl experts(n);
	vl deg(n),out(n);
	vvl depend(n);
	FOR(i,0,n) {
		cin >> experts[i] >> out[i];
		FOR(j,0,out[i]) {
			ll idx;
			cin >> idx;
            --idx;
			depend[i].pb(idx);
      deg[idx]++;
		}
	}

	set<pll> ready;
	FOR(i,0,n) {
		if(!deg[i]) {
			ready.emplace(experts[i], i);
		}
	}

	ll res = 0;
	FORD(todo,0,n) {
		pll cur = *ready.begin();
		ready.erase(cur);
		res = max(res, cur.xx + todo);
		for(auto idx : depend[cur.yy]) {
			if(!deg[idx]) {
				continue;
			}
			deg[idx]--;
			if(!deg[idx]) {
				ready.emplace(experts[idx], idx);
			}
		}
	}

	cout << res << endl;
}
