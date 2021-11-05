/* Sample solution to orienteering from NWERC'14.
 *
 * Bad Algorithm: check answer mod many small primes.
 *
 * Author: Per Austrin
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int N;
ll L, d[20][20];

const int MAX_MOD = 1000;

int MOD;
bool tried[14][1<<14][MAX_MOD];

bool PossModP(int at, int left, int x) {
	if (!left) return (x + d[at][0]) % MOD == L % MOD;
	bool &t = tried[at][left][x];
	if (!t) {
		t = true;
		for (int i = 1; i < N; ++i)
			if ((left & (1<<i)) && PossModP(i, left & ~(1<<i), (x+d[at][i])%MOD))
				return true;
	}
	return false;
}

bool PossCRT() {
	for (int p = 2; p <= MAX_MOD; ++p) {
		bool ok = true;
		for (int r = 2; ok && r*r <= p; ++r)
			ok &= !!(p % r);
		if (!ok) continue;
		MOD = p;
		memset(tried, 0, sizeof(tried));
		if (!PossModP(0, (1<<N)-2, 0)) return false;
	}
	return true;
}

int main(void) {
	scanf("%d%lld", &N, &L);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%lld", d[i]+j);
	printf("%s\n", PossCRT() ? "possible" : "impossible");
	return 0;
}
