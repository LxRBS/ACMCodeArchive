/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define MAXN 100000
#define ITERATIONS 500 // should be more than enough

int x[MAXN];
int y[MAXN];

// Is pt i on line p1 -- p2 ?
bool online(int i, int p1, int p2) {
	return (int64_t)(y[p2] - y[p1]) * (int64_t)(x[i] - x[p1])
		  == (int64_t)(y[i] - y[p1]) * (int64_t)(x[p2] - x[p1]);
}

int main() {
	int N, p, i, j, p1, p2, count;

	// Read input
	scanf("%d\n", &N);
	scanf("%d\n", &p);
	for(i = 0; i < N; i++)
		scanf("%d %d\n", &x[i], &y[i]);

	// Nasty corner-case, with one point it's always possible
	if(N == 1) {
		printf("possible\n");
		return 0;
	}
	
	// Pseudorandom numbers, be predictable
	srand(31337);

	// Iterate enough times to give correct answer with high probability
	for(i = 0; i < ITERATIONS; i++) {
		// Pick two arbitrary points
		p1 = rand() % N;
		p2 = rand() % N;
		if(p1 == p2) continue;
		
		// Check how many are on that line
		count = 2;
		for(j = 0; j < N; j++) {
			if(j == p1 || j == p2) continue;
			
			if(online(j, p1, p2)) count++;
		}

		// Is this a good line?
		if(count * 100 >= N * p) {
			printf("possible\n");
			return 0;
		}
	}

	// It is very unlikely that a line exists
	printf("impossible\n");

	return 0;
}
