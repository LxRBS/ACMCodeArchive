#pragma comment(linker, "/STACK:1024000000,1024000000")
/*
    Author: elfness@UESTC
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>

using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
#define PB push_back
#define fi first
#define se second
#define MP make_pair
const int ooo = 1000000000;
const LL oo = (LL) ooo * ooo;
const int P = 1000000007;

const int V = 100100;
vector<PII> f[V];
LL a[V], pre[V], inc[V], de[V];
LL dp[V][2];

LL cal(int u, int val) {
	if (a[u] < val) return (LL) inc[u] * (val - a[u]);
	else return de[u] * (a[u] - val);
}

void dfs(int u, int fa) {
	vector<PII> son;
	vector<LL> vals;
	for (int i = 0; i < f[u].size(); ++i) {
		int v = f[u][i].fi;
		LL w = f[u][i].se;
		if (v == fa) continue;
		pre[v] = w;
		dfs(v, u);
		son.PB(MP(w, v));
		vals.PB(w);
	}
	vals.PB(pre[u]);
	vals.PB(a[u]);
	dp[u][0] = dp[u][1] = oo;
	sort(son.begin(), son.end());
	int sz = son.size();
	sort(vals.begin(), vals.end());
	vector<LL> s(sz + 1);
	LL ps = -1, pb = 0;
	LL ss = 0, sb = 0;
	for (int i = 0; i < sz; ++i) {
		int v = son[i].se;
		LL w = son[i].fi;
		if (w == vals[0]) pb = i + 1;
		else sb += dp[v][1];
		s[i + 1] = s[i] + min(dp[v][0], dp[v][1]);
	}
	for (int i = 0; i < vals.size(); ++i) {
		LL val = vals[i];
		while (ps != sz - 1 && son[ps + 1].fi < val) {
			++ps;
			int v = son[ps].se;
			ss += dp[v][0];
		}
		while (pb != sz && son[pb].fi <= val) {
			int v = son[pb].se;
			sb -= dp[v][1];
			++pb;
		}
		LL se = s[pb] - s[ps + 1];
		LL st = 0;
		if (val <= pre[u]) dp[u][0] = min(dp[u][0], ss + se + sb + cal(u, val));
		if (val >= pre[u]) dp[u][1] = min(dp[u][1], ss + se + sb + cal(u, val));
	}
}

int _, n, u, v, w;
int main() {
	scanf("%d", &_);
	for (int ca = 1; ca <= _; ++ca) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", &inc[i]);
		//for (int i = 1; i <= n; ++i) scanf("%d", &de[i]);
		for (int i = 1; i <= n; ++i) de[i] = inc[i];
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for (int i = 1; i <= n; ++i) f[i].clear();
		for (int i = 1; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			f[u].PB(MP(v, w));
			f[v].PB(MP(u, w));
		}
		pre[1] = 0;
		dfs(1, -1);
		LL ans = min(dp[1][0], dp[1][1]);
		printf("%lld\n", ans);
	}
    return 0;
}

/*
2
3
2 1 2
9 9 10
1 2 10
1 3 11
3
1 1 2
9 9 10
1 2 10
1 3 11

*/
