#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define S(i,m) ((1<<i)&m)
typedef long long int ll;
ll m[16][16], N, L, possible;

int main() {
	cin >> N >> L;
	FOR(i, 0, N) FOR(j, 0, N) cin >> m[i][j];
	ll up = (1 << N), left = N/2 - 1;
	FOR(mid, 1, N) FOR(i, 0, up) {
		if (S(0,i) || S(mid,i) || __builtin_popcount(i) != left) continue;
		set<ll> lens;
		FOR(j, 0, 2) {
			vector<ll> route = {0};
			FOR(k, 1, N) if (k != mid && S(k, (j ? ~i : i))) route.push_back(k);
			route.push_back(mid);
			do {
				ll tot = 0;
				FOR(k, 0, (signed)route.size()-1) tot += m[route[k]][route[k+1]];
				if (!j) lens.insert(tot);
				else possible |= lens.find(L-tot) != lens.end();
			} while (next_permutation(route.begin() + 1, route.end() - 1));
		}
	}
	cout << (possible ? "possible" : "impossible") << endl;
	return 0;
}
