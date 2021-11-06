#include <bits/stdc++.h>
using namespace std;

const long long oo = 0x3f3f3f3f3f3f3f3f;

vector<long long> dijkstra(vector<vector<pair<int,int>>> adj, int s) {
	vector<long long> dist(adj.size(),oo);
	dist[s] = 0;
	set<pair<long long,int>> q;
	q.insert({0,s});

	while (q.size()) {
		int i = begin(q)->second;
		q.erase(begin(q));

		for (auto e: adj[i]) {
			int j = e.first, len = e.second;

			if (dist[j] <= dist[i] + len) continue;
			q.erase({dist[j],j});
			dist[j] = dist[i] + len;
			q.insert({dist[j],j});
		}
	}
	return dist;
}

int main() {
	long long a, b; cin >> a >> b;
	int n, m; cin >> n >> m;
	vector<vector<pair<int,int>>> adj(n);
	vector<vector<pair<int,int>>> rev_adj(n);
	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u-1].emplace_back(v-1,w);
		rev_adj[v-1].emplace_back(u-1,w);
	}
	adj[0].emplace_back(0,0);
	rev_adj[0].emplace_back(0,0);

	vector<long long> from_start = dijkstra(adj,0);
	vector<long long> to_finish = dijkstra(rev_adj,n-1);

	long long kmin = -1, kmax = 1e16;

	while (kmax-kmin > 1) {
		long long k = (kmin+kmax)/2;
		
		vector<bool> ok(n);
		vector<long long> latest(n,-oo);
		queue<int> q;

		for (int i = 0; i < n; i++) {
			if (to_finish[i] <= k && from_start[i]+to_finish[i] <= a+k) {
				ok[i] = true;
				latest[i] = a+k-to_finish[i];
				q.push(i);
			}
		}
		
		while (q.size()) {
			int i = q.front(); q.pop();
			for (auto e: adj[i]) {
				int j = e.first, len = e.second;
				if (!ok[j] && len+to_finish[j] <= k) {
					ok[j] = true;
					q.push(j);
				}
			}
		}

		vector<vector<pair<int,int>>> ok_adj(n);
		vector<int> indeg(n);
		for (int i = 0; i < n; i++) if (ok[i]) {
			for (auto e: adj[i]) {
				int j = e.first, len = e.second;
				if (ok[j] && len+to_finish[j] <= k) {
					ok_adj[i].push_back(e);
					indeg[j]++;
				}
			}
		}

		for (int i = 0; i < n; i++) if (ok[i] && indeg[i] == 0) q.push(i);

		while (q.size()) {
			int i = q.front(); q.pop();
			for (auto e: ok_adj[i]) {
				int j = e.first, len = e.second;
				if (ok[j]) {
					latest[j] = max(latest[j], latest[i] + len);
					if (--indeg[j] == 0) q.push(j);
				}
			}
		}
		
		bool possible = latest[n-1] >= b || accumulate(begin(indeg),end(indeg),0LL) > 0;
		if (possible) kmax = k; else kmin = k;
	}
	cout << kmax << endl;
}
