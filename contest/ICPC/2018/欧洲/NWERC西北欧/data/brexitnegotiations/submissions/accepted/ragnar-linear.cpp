#include <bits/stdc++.h>
using namespace std;
int main(){
	int n, ans = 0; cin >> n;
	vector<vector<int>> g(n);
	vector<int> m(n), d(n);
	for(int i = 0; i < n; ++i){
		cin >> m[i];
		int f; cin >> f;
		g[i].resize(f);
		for(auto &x : g[i]) cin >> x, --x, ++d[x];
	}
	priority_queue<pair<int,int>> q;
	for(int i = 0; i < n; ++i) if(d[i] == 0) q.push({-m[i],i});
	for(int b = n-1; b >= 0; --b){
		ans = max(ans, -q.top().first + b);
		int u = q.top().second; q.pop();
		for(auto v : g[u]) if(--d[v] == 0) q.push({-m[v], v});
	}
	cout << ans << endl;
}
