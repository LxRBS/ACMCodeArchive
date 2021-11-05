#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

const double inf = 1e50;
const int NN = 10005;

int n, P;

struct info {
	int p1, p2, t1, t2, w1, w2;
}A[NN];

double dp[2][101][7];

int main() {

	double cl = clock();
	while( scanf("%d %d", &n, &P) == 2 && n ) {
		for( int i = 1; i <= n; i++ ) scanf("%d %d %d %d %d %d", &A[i].p1, &A[i].p2, &A[i].t1, &A[i].t2, &A[i].w1, &A[i].w2);

		for( int i = 1; i <= 100; i++ ) for( int j = 0; j <= 6; j++ ) dp[0][i][j] = inf;
		dp[0][P][0] = 0;
		int cur = 1, prev = 0;
		for( int k = 1; k <= n; k++ ) {
			for( int i = 1; i <= 100; i++ ) for( int j = 0; j <= 6; j++ ) dp[cur][i][j] = inf;

			for( int i = 1; i <= 100; i++ ) for( int j = 0; j <= 6; j++ ) if( dp[prev][i][j] < inf && i >= A[k].p1 ) {
				int i1 = i + A[k].w1;
				int j1 = j + A[k].w2;

				if( i1 * (1 << j1) >= 100 ) i1 = 100, j1 = 0;

				double r;

				if( i >= A[k].p2 ) r = A[k].t2;
				else r = A[k].t2 + (A[k].p2 - i + 0.) * ( A[k].t1 - A[k].t2 ) / (A[k].p2 - A[k].p1);

				dp[cur][i1][j1] = min( dp[cur][i1][j1], r + dp[prev][i][j] );

			}

			for( int j = 6; j > 0; j-- ) for( int i = 1; i <= 100; i++ ) if( dp[cur][i][j] < inf ) {
				int i1 = min( i * 2, 100 );
				int j1 = j - 1;
				dp[cur][i1][j1] = min( dp[cur][i1][j1], dp[cur][i][j] );
			}

			swap( cur, prev );
		}
		double res = inf;
		for( int j = 6; j >= 0; j-- ) for( int i = 1; i <= 100; i++ ) res = min( res, dp[prev][i][j] );
		if(res > inf/2) printf("Impossible\n");
		else printf("%.2lf\n", res + 1e-11);
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}
