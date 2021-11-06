#include <bits/stdc++.h>
using namespace std;
int main(){
	int n; cin >> n;
	vector<vector<int>> g(n);
	vector<int> m(n), degrees(n);
	for(int i = 0; i < n; ++i){
		cin >> m[i];
		int d; cin >> d;
		g[i].resize(d);
		for(auto &x : g[i]) cin >> x, --x, ++degrees[x];
	}

	int l = 0, h = 1e6+n-1; // both inclusive; <= h is possible; < l is not possible
	while(l < h){
		int M = (l+h)/2;
		priority_queue<pair<int,int>> q;
		auto d = degrees;
		for(int i = 0; i < n; ++i) if(d[i] == 0) q.push({-m[i],i});
		for(int b = n-1; b >= 0; --b){
			if(q.empty()) goto end;
			// Process longer meetings first.
			int t = -q.top().first, u = q.top().second;
			q.pop();
			if(t + b > M) goto end;
			for(auto v : g[u]) if(--d[v] == 0) q.push({-m[v], v});
		}
		h = M; // good
		continue;
end:
		l = M+1; // bad
	}
	cout << l << endl;
}
