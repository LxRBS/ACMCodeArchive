/* Sample solution to DigiComp II from NWERC'14.
 *
 * Algorithm: toposort, keep track of #times each vertex is visited
 *
 * Author: Per Austrin
 */
#include <cstdio>
#include <cstring>

typedef long long ll;
int M, LR[1<<20][2], preds[1<<20], init[1<<20], Q[1<<20], qs = 0;
ll cnt[1<<20], N;

int main(void) {
	scanf("%lld%d", &N, &M);
	memset(preds, 0, sizeof(preds));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= M; ++i) {
		char dir[100];
		scanf("%s%d%d", dir, LR[i], LR[i]+1);
		init[i] = *dir == 'R';
		++preds[LR[i][0]];
		++preds[LR[i][1]];
	}
	for (int i = 1; i <= M; ++i) if (!preds[i]) Q[qs++] = i;
	cnt[1] = N;
	while (qs) {
		int v = Q[--qs];
		cnt[LR[v][init[v]]] += (cnt[v]+1)/2;
		cnt[LR[v][1-init[v]]] += cnt[v]/2;
		if (!--preds[LR[v][0]]) Q[qs++] = LR[v][0];
		if (!--preds[LR[v][1]]) Q[qs++] = LR[v][1];
	}
	for (int i = 1; i <= M; ++i)
		printf("%c", (init[i]+cnt[i])%2 ? 'R' : 'L');
	printf("\n");
}
