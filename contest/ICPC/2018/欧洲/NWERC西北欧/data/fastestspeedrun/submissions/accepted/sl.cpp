#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N;
	cin >> N;
	N++;
	ll res = 0;
	vector<vi> mat(N, vi(N));
	vi par(N);
	vector<vi> ch(N);
	ch[0].push_back(0);
	rep(i,1,N) {
		int x; ll t;
		cin >> x >> t;
		res += t;
		par[i] = x;
		rep(j,0,N) {
			cin >> mat[i][j];
			mat[i][j] -= t;
		}
		ch[x].push_back(i);
	}

	vi seen(N), best(N);
	function<int(int)> dfs = [&](int x) -> int {
		if (seen[x] == 2) return best[x];
		if (seen[x] == 1) return INT_MAX;
		seen[x] = 1;
		int r = x;
		trav(y, ch[x]) {
			r = max(r, dfs(y));
		}
		seen[x] = 2;
		best[x] = r;
		return r;
	};

	rep(start,0,N) {
		if (seen[start]) continue;
		if (dfs(start) == INT_MAX) { // cycle
			int minc = INT_MAX;
			int i = start, r = 0;
			do {
				int prev = i;
				i = par[i];
				r = max(r, i);
				trav(y, ch[i]) if (y != prev) {
					r = max(r, best[y]);
				}
				minc = min(minc, mat[i][N-1]);
			} while (i != start);
			res += minc;
			do {
				best[i] = r;
				rep(k,0,N) mat[i][k] -= minc;
				i = par[i];
			} while (i != start);
		}
	}

	vll dp(N, LLONG_MAX);
	dp[0] = 0;
	rep(i,0,N) {
		if (dp[i] == LLONG_MAX) continue;
		rep(j,0,N) {
			int y = best[j];
			if (y <= i) continue;
			dp[y] = min(dp[y], dp[i] + mat[j][i]);
		}
	}

	cout << res + dp[N-1] << endl;
}
