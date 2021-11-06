#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll LLINF = 1e17;
struct Edge{ int v; ll weight; };	// input edges
vector<vector<Edge>> g, gr;
struct PQ{ ll d; int v; };			// distance and target
bool operator>(const PQ &l, const PQ &r){ return l.d > r.d; }
vector<ll> dijkstra(const vector<vector<Edge>>&g, int s) {
	vector<ll> dist(g.size(),LLINF);
	priority_queue<PQ,vector<PQ>,greater<PQ>> pq;
	dist[s] = 0; pq.push({0, s});
	while (!pq.empty()) {
		auto d = pq.top().d; auto u = pq.top().v; pq.pop();
		if (d == dist[u])
			for(auto &e : g[u]) if (dist[e.v] > d + e.weight)
				pq.push({dist[e.v] = d + e.weight, e.v});
	}
	return dist;
}
int main(){
	ll a, b;
	int n, m; 
	cin >> a >> b >> n >> m;
	g.resize(n), gr.resize(n);
	while(m--){
		int u,v,w; cin >> u >> v >> w;
		--u, --v;
		g[u].push_back({v,w});
		gr[v].push_back({u,w});
	}
	g[0].push_back({0,0}), gr[0].push_back({0,0});
	auto ds = dijkstra(g, 0), dt = dijkstra(gr, n-1);
	ll l = 0, h = ds[n-1]+1; // target in [l,h]
	vector<vector<Edge>> ga(n), gar(n);
	while(l < h){
		ll m = (l+h)/2;
		
		// Graph of admissible edges.
		for(auto &v : ga) v.clear();
		for(auto &v : gar) v.clear();
		vector<int> din(n,0), dout(n,0);
		for(int u = 0; u < n; ++u) for(auto e : g[u])
				if(dt[e.v] + e.weight <= m) ga[u].push_back(e), ++dout[u];
		for(int u = 0; u < n; ++u) for(auto e : gr[u])
				if(dt[u] + e.weight <= m) gar[u].push_back(e), ++din[u];

		vector<int> pop;
		for(int u = 0; u < n; ++u) if(din[u] > 0 ^ dout[u] > 0) pop.push_back(u);
		while(!pop.empty()){
			int u = pop.back(); pop.pop_back();
			if(din[u] == 0)
				for(auto e : ga[u])
					if(--dout[u], --din[e.v] == 0) pop.push_back(e.v);
			if(dout[u] == 0)
				for(auto e : gar[u])
					if(--din[u], --dout[e.v] == 0) pop.push_back(e.v);
		}
		for(int u = 0; u < n; ++u) assert(((din[u] > 0) ^ (dout[u] > 0)) == false);

		vector<bool> cycle(n, false);
		for(int u = 0; u < n; ++u) cycle[u] = din[u] > 0 && dout[u] > 0;


		dout.assign(n,0);
		for(int u = 0; u < n; ++u) if(!cycle[u]) dout[u] = ga[u].size();

		vector<pair<ll,ll>> dp(n, {LLINF, -1});
		dp[n-1] = {-m, 0};
		for(int u = 0; u < n; ++u) if(cycle[u]){
			dp[u] = {dt[u]-m, LLINF};
		}

		pop.clear();
		for(int u = 0; u < n; ++u) if(dout[u] == 0) pop.push_back(u);

		
		bool ok = false;
		while(!pop.empty()){
			int u = pop.back();
			pop.pop_back();
			for(auto e : ga[u]){
				dp[u].first = min(dp[u].first, dp[e.v].first+e.weight);
				dp[u].second = max(dp[u].second, dp[e.v].second+e.weight);
			}
			if(dp[u].second < 0) dp[u].second == LLINF;
			if(dp[u].second > LLINF) dp[u].second = LLINF;
			if(ds[u] + dp[u].first <= a && a-dp[u].first+dp[u].second >=b){
				ok = true;
				break;
			}
			for(auto e : gar[u]) if(--dout[e.v] == 0) pop.push_back(e.v);
		}
		if(ok) h = m;
		else l = m+1;
	}
	cout << l << endl;
}
