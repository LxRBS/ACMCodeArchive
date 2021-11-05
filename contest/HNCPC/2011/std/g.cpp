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

const int NN = 205;
const int inf = 100000000;
const int MOD = 1000000009;

int n, A[NN][NN], val[NN][NN], dp[NN][NN], state[NN][NN], caseno;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int isvalid( int x, int y ) {
	return x >= 0 && x < n && y >= 0 && y < n && x <= y;
}

int call( int i, int j ) {
	if( i == 0 && j == n - 1 ) return 1;

	int &ret = dp[i][j];
	int &st = state[i][j];

	if( st == caseno ) return ret;
	st = caseno;

	ret = 0;

	for( int k = 0; k < 4; k++ ) {
		int x = i + dx[k];
		int y = j + dy[k];

		if( isvalid( x, y ) && val[x][y] + A[i][j] == val[i][j] ) ret = ( ret + call( x, y ) ) % MOD;
	}

	return ret;
}

int main() {
	double cl = clock();

	while( scanf("%d", &n) == 1 && n ) {
		for( int i = n - 1; i >= 0; i-- ) for( int j = 0; j < n; j++ ) scanf("%d", &A[j][i]);

		for( int i = 0; i < n; i++ ) for( int j = i + 1; j < n; j++ ) A[i][j] += A[j][i];

		for( int i = 0; i < n; i++ ) for( int j = i; j < n; j++ ) val[i][j] = inf;

		queue <int> Q;
		Q.push( 0 );
		Q.push( n - 1 );
		val[0][n - 1] = A[0][n - 1];

		while( !Q.empty() ) {
			int u = Q.front(); Q.pop();
			int v = Q.front(); Q.pop();

			for( int k = 0; k < 4; k++ ) {
				int x = u + dx[k];
				int y = v + dy[k];

				if( isvalid( x, y ) && val[x][y] > val[u][v] + A[x][y] ) {
					val[x][y] = val[u][v] + A[x][y];
					Q.push(x);
					Q.push(y);
				}
			}
		}
		int mn = inf, res = 0;
		for( int i = 0; i < n; i++ ) mn = min( mn, val[i][i] );

		++caseno;

		for( int i = 0; i < n; i++ ) if( val[i][i] == mn ) res = ( res + call( i, i ) ) % MOD;

		printf("%d\n", res);
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}
