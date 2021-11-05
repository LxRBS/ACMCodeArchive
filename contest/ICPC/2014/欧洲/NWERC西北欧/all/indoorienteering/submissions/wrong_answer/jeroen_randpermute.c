#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define ITERS 1000000
#define MAXN 14

int64_t dst[MAXN][MAXN];
int perm[MAXN];

int randInt(int min, int max) {
	return (int)floor(((double) rand() / (double)RAND_MAX) * (max-min+1)) + min;
}

void random_permute(int N) {
	int i, j, k;
	for(i = 1; i < N; i++) {
		j = randInt(0, i);
		k = perm[i];
		perm[i] = perm[j];
		perm[j] = k;
	}
}


int main() {
	int N, i, j;
	int64_t L, cur;
	scanf("%d %lld\n", &N, &L);
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			scanf("%lld", &dst[i][j]);

	for(i = 1; i < N; i++)
		perm[i-1] = i;

	for(i = 0; i < ITERS; i++) {
		random_permute(N-1);
		cur = dst[0][perm[0]] + dst[perm[N-2]][0];
		for(j = 0; cur <= L && j < N-2; j++) {
			cur += dst[perm[j]][perm[j+1]];
		}
		if(j == N - 2 && cur == L) {
			printf("possible\n");
			return 0;
		}
	}
	
	printf("impossible\n");
	
	return 0;
}
