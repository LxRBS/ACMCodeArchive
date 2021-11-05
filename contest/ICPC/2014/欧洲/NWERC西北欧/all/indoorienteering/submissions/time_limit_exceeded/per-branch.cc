#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int N;
long long L, d[20][20];

bool Poss(int at, int left, int end, long long T) {
	if (!left) return d[at][end] == T;
	if (T < 0) return false;
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
