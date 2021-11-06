#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m, q, c[N], d[N][1 << 7];
vector<int> ball[N];
vector<pair<int, int>> G[N];
int getmask(int i) {
	int res = 0;
	for (int x : ball[i]) res |= (1 << c[x]);
	return res;
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i < m; ++ i) {
		int u, v, t;
		scanf("%d%d%d", &u, &v, &t);
		G[u].push_back(make_pair(v, t));
		G[v].push_back(make_pair(u, t));
		assert(t >= 0 && t <= 10000);
	}
	for (int i = 0; i < q; ++ i) {
		int x, y;
		scanf("%d%d", &x, &y);
		ball[x].push_back(y);
		assert(1 <= y && y <= n);
	}
	int res = -1;
	for (int tries = 0; tries < 888; ++ tries) {
		for (int i = 1; i <= n; ++ i) c[i] = rand() % 7;
		priority_queue<pair<int, pair<int, int>>> q;
		for (int i = 1; i <= n; ++ i) {
			for (int j = 0; j < (1 << 7); ++ j) d[i][j] = -1;
		}
		d[1][getmask(1)] = 0;
		q.push(make_pair(0, make_pair(1, getmask(1))));
		while (!q.empty()) {
			auto p = q.top(); q.pop();
			int dis = -p.first, i = p.second.first, mask = p.second.second;
			if (dis != d[i][mask]) continue;
			if (res != -1 && dis > res) break;
			if (mask == (1 << 7) - 1) {
				if (res == -1) res = dis;
				res = min(res, dis);
				break;
			}
			for (auto e : G[i]) {
				int dd = dis + e.second;
				int mm = mask | getmask(e.first);
				int ii = e.first;
				if (d[ii][mm] == -1 || d[ii][mm] > dd) {
					d[ii][mm] = dd;
					q.push(make_pair(-dd, make_pair(ii, mm)));
				}
			}
		}
	}
	printf("%d\n", res);
}
