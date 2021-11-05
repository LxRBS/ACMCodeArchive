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

int m, n;
char bigp[15][15], smallp[15][15];

int countStar( char a[15][15], int n ) {
	int res = 0;
	for( int i = 0; i < n; i++ ) for( int j = 0; j < n; j++ ) res += ( a[i][j] == '*' );
	return res;
}

bool isValid( int x, int y ) {
	return x >= 0 && x < n && y >= 0 && y < n;
}

bool isSame( int i, int j ) {
	for( int x = 0; x < m; x++ ) for( int y = 0; y < m; y++ ) if( smallp[x][y] == '*' )
		if( !isValid( x + i, y + j ) || bigp[x+i][y+j] != '*' ) return false;
	return true;
}

bool canMatch( int k, int i, int j ) {
	if( !k ) return true;
	if( i == n ) return false;
	if( j == n ) return canMatch( k, i + 1, -10 );

	if( isSame( i, j ) ) {
		for( int x = 0; x < m; x++ ) for( int y = 0; y < m; y++ ) if( smallp[x][y] == '*' ) bigp[x+i][y+j] = '.';
		if( canMatch( k - 1, i, j ) ) return true;
		for( int x = 0; x < m; x++ ) for( int y = 0; y < m; y++ ) if( smallp[x][y] == '*' ) bigp[x+i][y+j] = '*';
	}
	return canMatch( k, i, j + 1 );
}

int main() {
	double cl = clock();

	while( scanf("%d %d", &n, &m) == 2 && m + n ) {
		for( int i = 0; i < n; i++ ) scanf("%s", bigp[i]);
		for( int i = 0; i < m; i++ ) scanf("%s", smallp[i]);

		int cnt1 = countStar( bigp, n );
		int cnt2 = countStar( smallp, m );

		if( cnt1 != cnt2 * 2 || !canMatch(2, -10, -10) ) puts("0");
		else puts("1");
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}
