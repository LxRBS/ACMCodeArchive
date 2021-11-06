#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[8][8], x[8], d[N], n, m;
vector<pair<int, int>> G[N];
void dijkstra(int st) {
	for (int i = 1; i <= n; ++ i) d[i] = -1;
	d[st] = 0;
	priority_queue<pair<int, int>> q;
	q.push(make_pair(0, st));
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		int dis = -p.first;
		if (d[p.second] != dis) continue;
		for (auto e : G[p.second]) {
			int dd = dis + e.second;
			if (d[e.first] == -1 || d[e.first] > dd) {
				d[e.first] = dd;
				q.push(make_pair(-dd, e.first));
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++ i) {
		int u, v, t;
		scanf("%d%d%d", &u, &v, &t);
		G[u].push_back(make_pair(v, t));
		G[v].push_back(make_pair(u, t));
	}
	for (int i = 1; i <= 7; ++ i) scanf("%d", &x[i]);
	x[0] = 1;
	for (int i = 0; i <= 7; ++ i) {
		dijkstra(x[i]);
		for (int j = 0; j <= 7; ++ j) {
			a[i][j] = d[x[j]];
		}
	}
	vector<int> p;
	for (int i = 0; i <= 7; ++ i) p.push_back(i);
	long long res = -1;
	do {
		int las = p[0];
		long long ans = 0;
		for (int i : p) {
			if (a[las][i] == -1) {
				ans = -1;
				break;
			}
			ans += a[las][i];
			las = i;
		}
		if (ans != -1) {
			if (res == -1) res = ans;
			res = min(res, ans);
		}
	} while (next_permutation(p.begin() + 1, p.end()));
	printf("%lld\n", res);
}

