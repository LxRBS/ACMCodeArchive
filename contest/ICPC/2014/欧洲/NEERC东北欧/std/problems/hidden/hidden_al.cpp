/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem H. Hidden Maze                                         */
/*                                                                */
/* Original idea         Alexander Kaluzhin                       */
/* Problem statement     Andrei Lopatin                           */
/* Test set              Andrei Lopatin                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Andrei Lopatin                           */
/******************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long int64;
typedef pair <int, int> pii;

#define forn(i, n) for (int i = 0; i < (int) n; i++)
#define seta(a, b) memset(a, b, sizeof(a))
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define last(a) a[a.size() - 1]
#define mp make_pair
#define fs first
#define sc second

const int NMAX = 30010;

int n, used[NMAX], h[NMAX], p[NMAX], d[NMAX], status[NMAX];
int64 ans, cnt;
vector<int> g[NMAX], w[NMAX];
vector<pii> edges;

struct Tstr {
	int n;
	vector<int> zn;

	Tstr() {
		Tstr(0);
	}

	Tstr(int n): n(n) {
		zn.resize(2 * n + 1);
		zn[n] = 1;
	}

	int& operator[](int idx) {
		return zn[idx + n];
	}

	int operator[](int idx) const {
		if (idx < -n || idx > n) return 0;
		return zn[idx + n];
	}
};

void add(Tstr& a, const Tstr& b, int sh) {
	for (int i = -b.n; i <= b.n; ++i) {
		a[i + sh] += b[i];
	}
}

void sub(Tstr& a, const Tstr& b, int sh) {
	for (int i = -b.n; i <= b.n; ++i)
		a[i + sh] -= b[i];
}

int64 mult(const Tstr& a, const Tstr& b, int sh) {
	int64 result = 0;
	for (int i = -b.n; i <= b.n; ++i)
		result += a[-(i + sh)] * b[i];
	return result;
}

Tstr str[NMAX];

void init(int v) {
	status[v] = 1;
	str[v] = Tstr(d[v]);
	used[v] = 1;
	forn(i, g[v].size())
		if (!used[g[v][i]]) {
			init(g[v][i]);
			add(str[v], str[g[v][i]], 1);
		}
}

void update(int v) {
	int now = 0, u = v;
	status[v] = 0;
	while (u != 0) {
		now += status[u];
		sub(str[p[u]], str[v], now + 1);
		add(str[p[u]], str[v], now - 1);
		u = p[u];
	}
	status[v] = -1;
}

int64 calc(int v) {
	int64 result = 0;
	int now = -status[v], u = v;
	while (u != 0) {
		now += status[u];
		result += mult(str[p[u]], str[v], now);
		result -= mult(str[u], str[v], now + status[u]);
		u = p[u];
	}
	return result;
}

void dfs(int v, int vv, int hh) {
	h[v] = hh;
	p[v] = vv;
	d[v] = 0;
	used[v] = 1;
	forn(i, g[v].size())
		if (!used[g[v][i]]) {
			dfs(g[v][i], v, hh + 1);
			d[v] = max(d[v], 1 + d[g[v][i]]);
		}
}

int main() {
	freopen("hidden.in", "rt", stdin);
	freopen("hidden.out", "wt", stdout);
	cin >> n;
	forn(i, n - 1) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		x--, y--;
		g[x].pb(y);
		w[x].pb(z);
		g[y].pb(x);
		w[y].pb(z);
	}

	ans = 0, cnt = 0;
	seta(used, 0);
	dfs(0, 0, 0);
	seta(used, 0);
	init(0);

	forn(i, n)
		forn(j, g[i].size())
			if (h[i] > h[g[i][j]])
				edges.pb(mp(w[i][j], i));
	sort(all(edges));

	forn(i, edges.size()) {
		int64 ept = calc(edges[i].sc);
		ans += ept * 1LL * edges[i].fs;
		cnt += ept;
		update(edges[i].sc);
	}

	printf("%.10lf\n", ans * 1. / cnt);

	return 0;
}
