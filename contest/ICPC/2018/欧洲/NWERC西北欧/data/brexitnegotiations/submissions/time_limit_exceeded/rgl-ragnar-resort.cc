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
	vector<pair<int,int>> q;
	for(int i = 0; i < n; ++i) if(d[i] == 0) q.emplace_back(-m[i],i);
  sort(q.begin(),q.end());
	for(int b = n-1; b >= 0; --b){
		ans = max(ans, -q.back().first + b);
		int u = q.back().second; q.pop_back();
		for(auto v : g[u]) if(--d[v] == 0){
      q.emplace_back(-m[v], v);
    }
    sort(q.begin(),q.end());
	}
	cout << ans << endl;
}
