/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000
#define MAXD 20
#define INF 2000000000

#define MIN(a,b) ((a) < (b) ? (a) : (b))

int price[MAXN];
int accum[MAXN+1];
int DP[MAXN+1][MAXN+1][MAXD+1];

int myround(int a) {
	return (a + 5) / 10 * 10;
}

int main() {
	int N, D, i, j, k, ret;

	// Read input
	scanf("%d %d\n", &N, &D);
	
	for(i = 0; i < N; i++)
		scanf("%d", &price[i]);

	// Init, should be a nice memset
	for(i = 0; i <= N; i++)
		for(j = 0; j <= N; j++)
			for(k = 0; k <= D; k++)
				DP[i][j][k] = INF;

	accum[0] = 0;
	for(i = 0; i < N; i++)
		accum[i+1] = accum[i] + price[i];

	// DP
	DP[0][0][0] = 0;
	for(i = 0; i < N; i++) {
		for(j = 0; j <= i; j++) {
			for(k = 0; k <= D; k++) {
				// Do not place bar before this item
				DP[i+1][j][k] = MIN(DP[i+1][j][k], DP[i][j][k]);

				if(k < D) {
					// Do place bar
					DP[i+1][i][k+1] = MIN(DP[i+1][i][k+1],
					                      DP[i][j][k] + myround(accum[i] - accum[j]));
				}
			}
		}
	}

	// Find and print answer	
	ret = INF;
	for(i = 0; i < N; i++)
		for(j = 0; j <= D; j++)
			ret = MIN(ret, DP[N][i][j] + myround(accum[N] - accum[i]));
	printf("%d\n", ret);

	return 0;
}
