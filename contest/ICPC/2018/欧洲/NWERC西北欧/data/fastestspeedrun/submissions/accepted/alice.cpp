#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
#define FOR(i,a,b) for (ll i=(a); i<(b); i++)
#define FORD(i,a,b) for (ll i=ll(b)-1; i>=(a); i--)

//std cycle represent finding
void cycle_represent(ll cur, vl& pre, vl& repr, vb& visited){
	if(visited[cur]) return;
	repr[cur] = cur;
	visited[cur] = true;
	if(pre[cur] != -1){ //out of bounds otherwise -.-
		cycle_represent(pre[cur], pre, repr, visited);
		repr[cur] = repr[pre[cur]];
	}
}

int main() {

	cin.sync_with_stdio(0);
	cin.tie(0);

	ll fixcost = 0;

	ll n, s;
	cin >> n;

	vl pre(n);
	vvl a(n, vl(n+1));
	vb visited(n);
	vl repr(n);

	vvl cost(n, vl(n+1));
	vector<vb> visited_other(n, vb(n+1));

	FOR(i, 0, n){
		cin >> pre[i] >> s;
		FOR(j, 0, n+1){
			cin >> a[i][j];
			a[i][j] -= s;
			assert(a[i][j] >= 0);
		}
		fixcost += s;
		pre[i]--;
	}

	FOR(i, 0, n){
		cycle_represent(i, pre, repr, visited);
	}

	FOR(i, 0, n){
		if(repr[i] != i) continue;
		if(pre[i] == -1) continue;

		set<ll> cic;
		ll cur = i;
		while(true){
			cic.insert(cur);
			cur = pre[cur];
			if(cur == i) break;
		}

		ll mi = a[*cic.begin()][n];
		for(auto& c : cic)
			mi = min(mi, a[c][n]);

		for(auto& c : cic) FOR(i, 0, n+1) a[c][i] -= mi;
		fixcost += mi;

	}

	FOR(i, 0, n) a[i][pre[i]+1] = 0;

	//dijkstra
	ll act = 0;
	vl dist(n+1, oo);
	dist[0] = 0;
	vl d_visited(n+1);
	while(true){
		if(act == n) break;
		d_visited[act] = true;
		FOR(i, 1, n+1){
			dist[i] = min(dist[i], dist[act] + a[i-1][act]);
		}
		ll mi = oo;
		FOR(i, 1, n+1){
			if(d_visited[i] != true){
				if(dist[i] <= mi){
					act = i;
					mi = dist[i];
				}
			}
		}
	}

	cout << dist[n] + fixcost << endl;
}
