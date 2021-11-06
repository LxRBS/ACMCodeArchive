#include <bits/stdc++.h>

#define sz(c) ll((c).size())
#define FOR(i,a,b) for(ll i=(a); i<(b); i++)
#define xx first
#define yy second

using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;

int main(){
	ll n;
	cin >> n;

	vector<vl> adj(n);
	vl es(n);
	vl dis(n);
	FOR(i, 0, n){
		cin >> es[i] >> dis[i];
		FOR(j, 0, dis[i]){
			ll x;
			cin >> x;
			x--;
			adj[x].push_back(i);
		}
	}

	ll mx = 00;

	priority_queue<pll> q;
	FOR(i, 0, n) if(!dis[i]) q.push({es[i], i});

	ll c = 0;
	while(q.size()){
		pll act = q.top(); q.pop();
		ll cost = act.xx + c;
		mx = max(mx, cost);
		//cerr << act.yy << ": " << act.xx << " " << cost << endl;

		for(auto& a : adj[act.yy]){
			if(--dis[a] == 0){
				q.push({es[a], a});
			}
		}

		c++;
	}

	cout << mx << endl;

}
