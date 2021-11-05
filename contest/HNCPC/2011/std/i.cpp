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

typedef long long i64;

const int MOD = 1000000009;
const int NN = 256;

// recurrence: f(n, k) = f(n-k, k) + f(n-k, k-1) * 4 + f(n-k, k-2) * 6 + f(n-k, k-3) * 4 + f(n-k, k-4)

int n, k, N, pos[18][18];;
int base[NN][NN], res[NN][NN], temp[NN][NN];

int multiply( int A[NN][NN], int B[NN][NN], int C[NN][NN] ) {
	for( int i = 0; i < N; i++ ) for( int j = 0; j < N; j++ ) {
		temp[i][j] = 0;
		for( int k = 0; k < N; k++ ) if( A[i][k] && B[k][j] ) temp[i][j] = ( temp[i][j] + A[i][k] * (i64)B[k][j] ) % MOD;
	}
	for( int i = 0; i < N; i++ ) for( int j = 0; j < N; j++ ) C[i][j] = temp[i][j];
}

void buildBase() {
	for( int i = 0; i < N; i++ ) {
		for( int j = 0; j < N; j++ ) base[i][j] = res[i][j] = 0;
		res[i][i] = 1;
	}
	// build base
	int x = 0;
	for( int j = k; j >= 1; j-- ) for( int i = k + 1; i > 1; i-- ) {
		if( pos[i][j] == -1 ) {
			int p = i - j, q = j;
			if( p >= 1 ) {
				assert( pos[p][q] > -1 ); base[x][ pos[p][q] ] = 1;
				q--;
				if( q > 0 ) {
					assert( pos[p][q] > -1 ); base[x][ pos[p][q] ] = 4;
					q--;
					if( q > 0 ) {
						assert( pos[p][q] > -1 ); base[x][ pos[p][q] ] = 6;
						q--;
						if( q > 0 ) {
							assert( pos[p][q] > -1 ); base[x][ pos[p][q] ] = 4;
							q--;
							if( q > 0 ) {
								assert( pos[p][q] > -1 ); base[x][ pos[p][q] ] = 1;
							}
						}
					}
				}
			}
		}
		else base[x][ pos[i][j] ] = 1;
		x++;
	}
}

int solve() {
	int dp[20][17] = {0};

	dp[0][0] = 1;
	for( int i = 1; i < 20; i++ ) {
		for( int j = 1; j <= k; j++ ) {
			int p = i - j, q = j;
			if( p >= 0 && q >= 0 ) dp[i][j] = (dp[i][j] + dp[p][q]) % MOD;
			q--; if( p >= 0 && q >= 0 ) dp[i][j] = (dp[i][j] + 4 * (i64) dp[p][q]) % MOD;
			q--; if( p >= 0 && q >= 0 ) dp[i][j] = (dp[i][j] + 6 * (i64) dp[p][q]) % MOD;
			q--; if( p >= 0 && q >= 0 ) dp[i][j] = (dp[i][j] + 4 * (i64) dp[p][q]) % MOD;
			q--; if( p >= 0 && q >= 0 ) dp[i][j] = (dp[i][j] + dp[p][q]) % MOD;
		}
	}
	if( n < 20 ) {
		int r = 0;
		for( int i = 1; i <= k; i++ ) r = ( r + dp[n][i] ) % MOD;
		return r;
	}
	int f[NN] = {0}, f1[NN] = {0};
	N = 0;
	memset( pos, -1, sizeof(pos) );
	for( int i = k; i >= 1; i-- ) for( int j = k; j >= 1; j-- ) {
		f[N] = dp[j][i];
		pos[j][i] = N++;
	}

	buildBase();

	int p = n - k;

	while( p ) {
		if( p & 1 ) multiply( res, base, res );
		multiply( base, base, base );
		p >>= 1;
	}

	for( int i = 0; i < N; i++ ) for( int k = 0; k < N; k++ ) if( f[k] && res[i][k] ) f1[i] = (f1[i] + res[i][k] * (i64)f[k]) % MOD;

	int r = 0;
	for( int i = 0; i < N; i += k ) r = ( r + f1[i] ) % MOD;
	return r;
}

int main() {
	double cl = clock();

	while( scanf("%d %d", &n, &k) == 2 && n ) {
		printf("%d\n", solve());
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}
