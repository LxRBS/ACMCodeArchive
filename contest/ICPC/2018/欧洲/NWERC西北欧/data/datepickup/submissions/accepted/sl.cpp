#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/SCC.h
vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	trav(e,g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

struct Edge {
	int target;
	ll length;
	int eind;
};

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N, M;
	ll A, B;
	cin >> A >> B;
	// To be able to assert that the solution is an integer, scale distances up.
	A *= 2;
	B *= 2;
	cin >> N >> M;
	vector<vector<Edge>> ed(N), revEd(N);
	rep(i,0,M) {
		int u, v, t;
		cin >> u >> v >> t;
		t *= 2;
		--u, --v;
		ed[u].push_back(Edge{v, t, i});
		revEd[v].push_back(Edge{u, t, i});
	}

	auto works = [&](ll maxDelay) {
		// Compute how good each road is
		priority_queue<pair<ll, int>> pq;
		pq.push({0, N-1});
		vi seen(N);
		vector<ll> covers(M, -1);
		vector<vi> rg(N);
		vector<vector<ll>> rg2(N);
		while (!pq.empty()) {
			ll dist;
			int ind;
			tie(dist, ind) = pq.top();
			dist = -dist;
			pq.pop();
			if (seen[ind]++) continue;
			trav(e, revEd[ind]) {
				ll cover = min(maxDelay - dist, e.length);
				covers[e.eind] = cover;
				if (cover == e.length) {
					pq.push({-(dist + e.length), e.target});
					rg[e.target].push_back(ind);
					rg2[e.target].push_back(e.length);
				}
			}
		}

		// If node 0 is good, we can just wait for the signal.
		if (seen[0]) return true;

		// Compute how far each node can travel along good roads (-1 = can't reach end)
		const ll inf = LLONG_MAX / 3;
		vector<ll> reach(N, -1);
		scc(rg, [&](vi c) {
			bool cycle = true;
			if (sz(c) == 1) {
				// Detect self-edges
				cycle = (count(all(rg[c[0]]), c[0]) > 0);
			}
			if (cycle) {
				trav(x, c) reach[x] = inf;
			} else {
				assert(sz(c) == 1);
				int x = c[0];
				ll r = (x == N-1 ? 0 : -1);
				rep(i,0,sz(rg[x])) {
					int target = rg[x][i];
					ll len = rg2[x][i];
					if (reach[target] == -1) continue;
					r = max(r, reach[target] + len);
				}
				reach[x] = min(r, inf);
			}
		});

		// We know that we need to be moving when the signal sounds; thus we
		// need to reach a good road part in time <= A. Determine whether
		// that's possible.
		pq.push({0, 0});
		seen.assign(N, 0);
		while (!pq.empty()) {
			ll dist;
			int ind;
			tie(dist, ind) = pq.top();
			dist = -dist;
			pq.pop();
			if (seen[ind]++) continue;
			if (reach[ind] >= B-A) return true;
			trav(e, ed[ind]) {
				if (covers[e.eind] < e.length) {
					ll part = e.length - covers[e.eind];
					if (dist + part <= A && reach[e.target] != -1 &&
							covers[e.eind] + reach[e.target] >= B-A) {
						return true;
					}
				}
				if (dist + e.length <= A)
					pq.push({-(dist + e.length), e.target});
			}
		}
		return false;
	};

	ll lo = -1, hi = 1LL << 61;
	while (lo + 1 < hi) {
		ll mid = (lo + hi) / 2;
		if (works(mid)) hi = mid;
		else lo = mid;
	}
	assert(hi % 2 == 0);
	cout << (hi / 2) << endl;
}
