#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<long long, long long> pii;
int N;
long long L, d[20][20];
int ITERS = 0;
const int MAX_ITERS = 150000000;

pii drange[15][15][1<<15];

pii DRange(int at, int left, int end) {
	if (!left) return pii(d[at][end], d[at][end]);
	pii &res = drange[end][at][left];
	if (res.first == 0) {
		res.first = 1<<30;
		res.second = 0;
		for (int i = 1; i < N; ++i)
			if ((left & (1<<i))) {
				pii sub = DRange(i, left & ~(1<<i), end);
				res.first = min(res.first, d[at][i]+sub.first);
				res.second = max(res.second, d[at][i]+sub.second);
			}
	}
	return res;
}

bool Poss(int at, int left, int end, long long T) {
	if (!left) return d[at][end] == T;
	pii R = DRange(at, left, end);
	if (T < R.first || T > R.second) return false;
	if (T == R.first || T == R.second) return true;
	if (++ITERS >= MAX_ITERS) return false;
	for (int i = 1; i < N; ++i)
		if ((left & (1<<i)) && Poss(i, left & ~(1<<i), end, T-d[at][i]))
			return true;
	return false;
}

bool Poss() {
	if (N == 2) return d[0][1] + d[1][0] == L;
	for (int i = 1; i < N; ++i)
		for (int j = 1; j < i; ++j)
			if (Poss(i, (1<<N)-1-(1<<0)-(1<<i)-(1<<j), j, L-d[0][i]-d[0][j]))
				return true;
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
