/* Sample solution to Cent Savings from NWERC'14.
 *
 * Algorithm: O(I*D) dynprog keeping track of what item we're at, how
 * many dividers are left, and current cost mod 10
 *
 * Author: Per Austrin
 */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int I, D, C[2000];
int best[2000][100][10];

int Best(int i, int d, int c) {
	if (i == I) return c < 5 ? c : c-10;
	int &r = best[i][d][c];
	if (!r) {
		r = Best(i+1, d, (c+C[i])%10);
		if (d) r = max(r, (c < 5 ? c : c-10) + Best(i+1, d-1, C[i]%10));
		r += 10000;
	}
	return r - 10000;
}

int main(void) {
	int S = 0;
	scanf("%d%d", &I, &D);
	for (int i = 0; i < I; ++i)
		scanf("%d", C+i), S += C[i];
	memset(best, 0, sizeof(best));
	printf("%d\n", S-Best(0, D, 0));
	return 0;
}
