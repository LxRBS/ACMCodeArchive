#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
#define FOR(i,a,b) for (ll i=(a); i<(b); i++)
#define FORD(i,a,b) for (ll i=ll(b)-1; i>=(a); i--)
const ll DEBUG = 0;

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

void cycle_least_cost(ll cur1, ll cur2, vl& pre, vvl& cost, vvl& a, vector<vb>& visited){
	if(visited[cur1][cur2]) return;
	cost[cur1][cur2] = a[cur1][cur2];
	visited[cur1][cur2] = true;
	if(pre[cur1] != -1){
		cycle_least_cost(pre[cur1], cur2, pre, cost, a, visited);
		cost[cur1][cur2] = min(cost[cur1][cur2], min(cost[pre[cur1]][cur2], a[cur1][cur2]));
	} else {
		cost[cur1][cur2] = 0;
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
		if(DEBUG) cerr << repr[i] << endl;
	}

	//if(DEBUG) cerr << fixcost << endl;

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

	if(DEBUG){
		FOR(i, 0, n){
			FOR(j, 0, n+1){
				cerr << a[i][j] << " ";
			}
			cerr << endl;
		}
	}

	FOR(i, 0, n){
		FOR(j, 0, n+1){
			cycle_least_cost(i, j, pre, cost, a, visited_other);
		}
		if(DEBUG){

			cerr << "just calc" << endl;
			FOR(j, 0, n+1){
				cerr << cost[i][j] << " ";
			}
			cerr << endl;
		}
	}
	visited_other = vector<vb>(n, vb(n+1));
	FOR(i, 0, n){
		FOR(j, 0, n+1){
			if(pre[i] != -1){
				cost[i][j] = min(cost[i][j], cost[pre[i]][j]);
				//kkcycle_least_cost(i, j, pre, cost, a, visited_other);
			}
		}
	}

	if(DEBUG) cerr << endl;

	if(DEBUG){
		FOR(i, 0, n){
			FOR(j, 0, n+1){
				cerr << cost[i][j] << " ";
			}
			cerr << endl;
		}
	}

	//reversed dp is more intuitive for me tbh
	vl dp(n+1);
	FORD(i, 0, n){
		dp[i] = oo;
		FOR(j, i, n){
			if(DEBUG) { cerr << "from " << i << " to  " << j << ": ";
				cerr << dp[j] <<  " + " << ll(cost[i][j+1]) << " = " << (dp[j] + cost[i][j+1]) << endl;
			}
			if(dp[j+1] != oo){
				dp[i] = min(dp[i], dp[j+1] + cost[j][i]);
			}
		}
		if(DEBUG){ cerr << dp[i] << endl;}
	}

	if(DEBUG) cerr << fixcost << endl;
	cout << dp[0] + fixcost << endl;
}
