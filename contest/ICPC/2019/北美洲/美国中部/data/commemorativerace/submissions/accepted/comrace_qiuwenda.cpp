#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int vis[N], d[N], d2[N], cnt[N], ans[N];
vector<int> G[N];
int dfs(int x) {
	if (vis[x] == 1) return d[x];
	vis[x] = 1;
	for (int u : G[x]) {
		int tmp = dfs(u) + 1;
		if (tmp > d[x]) {
			d2[x] = d[x];
			d[x] = tmp;
		}
		else if (tmp > d2[x]) {
			d2[x] = tmp;
		}
	}
	return d[x];
}
void dfs2(int x, int d_up = 0) {
	if (vis[x] == 2) return;
	vis[x] = 2;
	for (int u : G[x]) {
		if (d[x] == d[u] + 1) {
			dfs2(u, d_up + 1);
			cnt[d_up] ++;
			ans[d_up] = d_up + d2[x];
		}
	}
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) G[0].push_back(i);
	for (int i = 0; i < m; ++ i) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
	}
	dfs(0);
	dfs2(0);
	int res = d[0];
	for (int i = 1; i <= n; ++ i) if (cnt[i] == 1) res = min(res, ans[i]);
	printf("%d\n", res - 1);
}

