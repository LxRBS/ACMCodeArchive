#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<int> indeg(n), outdeg(n), val(n);
	vector<vector<int>> adj(n);

	for (int i = 0; i < n; i++) {
		cin >> val[i] >> outdeg[i];
		for (int j = 0; j < outdeg[i]; j++) {
			int k; cin >> k;
            --k;
			adj[i].push_back(k);
      indeg[k]++;
		}
	}

	set<pair<int,int>> q;
	for (int i = 0; i < n; i++) if (indeg[i] == 0) q.emplace(val[i],i);

	int res = 0;
	while (!q.empty()) {
		int i = begin(q)->second;
		q.erase(begin(q));
		res = max(res, val[i] + --n);
		for (int j: adj[i]) if (--indeg[j] == 0) q.emplace(val[j],j);
	}
	cout << res << endl;
}
