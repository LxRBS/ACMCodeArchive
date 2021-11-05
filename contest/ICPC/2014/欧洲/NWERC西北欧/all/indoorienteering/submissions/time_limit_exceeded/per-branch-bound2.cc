#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
int N;
long long L, d[20][20];

const int MAX_VALS = 30;

struct data {
	long long lo, hi;
	set<long long> values;
};
data drange[15][1<<15];

const data &DRange(int at, int left, int end) {
	if (!left) {
		drange[at][left].lo = drange[at][left].hi = d[at][end];
		drange[at][left].values.clear();
		drange[at][left].values.insert(d[at][end]);
		return drange[at][left];
	}
	data &res = drange[at][left];
	if (res.lo == -1) {
		res.lo = 1<<30;
		res.hi = 0;	
		res.values.clear();
		for (int i = 1; i < N; ++i)
			if ((left & (1<<i))) {
				data sub = DRange(i, left & ~(1<<i), end);
				res.lo = min(res.lo, d[at][i]+sub.lo);
				res.hi = max(res.hi, d[at][i]+sub.hi);
				for (auto x: sub.values) {
					if (res.values.size() > MAX_VALS) break;
					res.values.insert(d[at][i]+x);
				}
			}
	}
	return res;
}

bool Poss(int at, int left, int end, long long T) {
	if (!left) return d[at][end] == T;
	const data &R = DRange(at, left, end);
	if (T < R.lo || T > R.hi) return false;
	if (T == R.lo || T == R.hi || R.values.find(T) != R.values.end()) return true;
	if (R.values.size() < MAX_VALS) return false;
	for (int i = 1; i < N; ++i)
		if ((left & (1<<i)) && Poss(i, left & ~(1<<i), end, T-d[at][i]))
			return true;
	return false;
}

bool Poss() {
	if (N == 2) return d[0][1] + d[1][0] == L;
	for (int i = 1; i < N; ++i) {
		for (int k = 0; k < N; ++k)
			for (int S = 0; S < (1<<N); ++S)
				drange[k][S].lo = -1;
		for (int j = 1; j < i; ++j)
			if (Poss(j, (1<<N)-1-(1<<0)-(1<<i)-(1<<j), i, L-d[0][i]-d[0][j]))
				return true;
	}
	return false;
}

int main(void) {
	scanf("%d%lld", &N, &L);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%lld", d[i]+j);
	printf("%s\n", Poss() ? "possible" : "impossible");
	return 0;
}
