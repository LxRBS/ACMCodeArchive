#include <cstdio>
#include <algorithm>

int T;
long long P, Q;

long long dfs(long long S, long long T, long long step, long long stop) {
	//printf("%lld %lld %lld %lld\n", S, T, step, stop);
	if (S == T) return step;
	long long x = 0;
	while (S - (1 << x) + 1 > T) x++;
	if (S - (1 << x) + 1 == T) return step + x;
	long long up = (T - std::max((long long)0, S - (1 << x) + 1));
	long long tmp = x + std::max((long long)0, up - stop);
	return std::min(tmp + step, dfs(S - (1 << (x - 1)) + 1, T, step + x, stop + 1));
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &P, &Q);
		if (Q >= P) {
			printf("%lld\n", Q - P);
			continue;
		}
		printf("%lld\n", dfs(P, Q, 0, 0));
	}
	return 0;
}
