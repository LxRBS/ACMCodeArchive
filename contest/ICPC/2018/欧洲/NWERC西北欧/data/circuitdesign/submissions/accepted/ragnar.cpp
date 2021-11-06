#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> g;
vector<pair<double,double>> ans;
double A;
void dfs(int u, int p, double x, double y, double& a){
	for(int v : g[u]) if(v!=p) dfs(v, u, ans[v].first = x+cos(a), ans[v].second = y+sin(a), a), a+=A;
}
int main(){
	int n; cin >> n;
	A = acos(-1) / (n-1); // All lines go up with angle in [0, pi)
	g.resize(n); ans.resize(n);
	for(int i = 0; i < n-1;++i){
		int u,v; cin >> u >> v; --u, --v;
		g[u].push_back(v); g[v].push_back(u);
	}
	double a = 0;
	dfs(0, -1, 0, 0, a);
	cout << setprecision(7) << fixed;
	for(auto p : ans) cout << p.first << ' ' << p.second << '\n';
}
