#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	int n; cin >> n;
	vector<int> p(n+1, -1);
	vector<vector<int>> c(n+1);
	vector<vector<ll>> a(n+1, vector<ll>(n+1, 0));
	ll ans = 0;
	for(int i = 1; i <= n; ++i){
		cin >> p[i];
		c[p[i]].push_back(i);
		ll x; cin >> x; ans += x;
		for(auto &y : a[i]) cin >> y, y-=x;
	}
	for(int u = 0; u <= n; ++u){  // Contract cycles.
		int t = u, h = p[u];      // tortoise+hare cycle finding
		while(h >= 0 && p[h] >= 0 && t != h) t=p[t], h=p[p[h]];
		if(h < 0 || p[h] < 0) continue;
		vector<int> cycle;        // Find the cycle elements.
		do{
			cycle.push_back(t);
			t = p[t];
		} while(t != h);
		int m = *max_element(cycle.begin(), cycle.end());
		for(auto x : cycle){      // Compress to the max element.
			p[x] = -3;
			for(int i = 0; i <= n; ++i) a[m][i] = min(a[m][i], a[x][i]);
			for(auto y : c[x]) p[y] = m;
		}
		p[m] = -2;
		ans += a[m][n];
		for(auto &x : a[m]) x-=a[m][n];
	}
	vector<int> mc(n+1, -1), order;  // Find max child of each vertex.
	function<void(int, int)> dfs = [&](int v, int u){
		if(v>=0 && p[v] >= -2 && mc[v] == -1)
			mc[v] = u, dfs(p[v], u), order.push_back(v);
	};
	for(int u=n; u >= 0; --u) dfs(u, u);
	vector<ll> cost(order.size(), 1e18); // cost[i]: cheapest way to buy node in order[i].
	for(int i = order.size()-1; i >= 0; --i){
		int u = order[i];
		cost[i] = a[u][0];
		for(int j = i+1; j < order.size(); ++j)
			cost[i] = min(cost[i], cost[j]+a[u][mc[order[j]]]);
	}
	cout << ans + cost[0] << endl;
}
