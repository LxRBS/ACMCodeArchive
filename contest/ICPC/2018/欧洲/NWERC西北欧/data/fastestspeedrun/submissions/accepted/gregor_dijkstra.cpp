#include <bits/stdc++.h>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)


vll adj[2600][2]; // input: graph and rev. graph
ll ccomp, comp[2600]; // output: component of each node
vll st; // temp: stack

void dfs(ll n, ll c, ll dir) {
	if (comp[n] != -1) return;
	comp[n] = c;
	FOR(i, 0, sz(adj[n][dir]))
		dfs(adj[n][dir][i], c, dir);
	if (!dir) st.push_back(n);
}

void kosaraju(ll n) {
	memset(comp, -1, sizeof(comp));
	st.clear();

	FOR(i, 0, n) dfs(i, 0, 0);

	reverse(all(st));
	memset(comp, -1, sizeof(comp));
	ccomp = 0;

	FOR(i, 0, sz(st))
		if (comp[st[i]] == -1) dfs(st[i], ccomp++, 1);
}


ll a[2600][2600];
ll dp[2600];

int main(){
	int n; cin >> n;
	ll total = 0;
	FOR(i,0,n){
		ll x, t; cin >> x >> t;
		// edge x -> y   ===   level i depends on gimmick x
		adj[i+1][0].push_back(x);
		adj[x][1].push_back(i+1);

		total += t;
		FOR(j,0,n+1){
			cin >> a[i+1][j];
			a[i+1][j] -= t;
		}
		a[i+1][x] = 0;
	}

	// find SCCs in dependency graph and then "reduce"
	kosaraju(n+1);

	map<int,set<int>> comps;
	FOR(i,0,n+1) comps[comp[i]].insert(i);

	FORIT(co,comps) if(co->second.size() > 1 ||
		   (*(co->second.begin()) != 0 &&
		   	adj[*(co->second.begin())][0][0] == *(co->second.begin()))) {
		
		ll mini = oo;
		FORIT(el,co->second) mini = min(mini, a[*el][n]);

		FORIT(el,co->second) FOR(j,0,n+1) a[*el][j] -= min(a[*el][j],mini);
		total += mini;
	}

	dp[0] = 0;
	FOR(i,1,n+1) dp[i] = oo;
	priority_queue<pll> q;
	q.push(make_pair(0,0));

	while (q.size()){
		pll t = q.top(); q.pop();
		if (-t.first != dp[t.second]) continue;
		FOR(i,1,n+1) if (dp[t.second] + a[i][t.second] < dp[i])
			dp[i] = dp[t.second] + a[i][t.second], q.push(make_pair(-dp[i],i));
	}
	
	cout << total + dp[n] << endl;
}
