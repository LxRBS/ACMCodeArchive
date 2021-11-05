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

const int NN = 1 << 18;
const int inf = 1000000000;

int n, q, A[NN], pos[NN], test, T[NN], C[50], update[NN];

void makeTree( int idx, int low, int high ) {
	if( low == high ) {
		T[idx] = A[low];
		pos[low] = idx;
		update[idx] = 0;
		return;
	}

	int mid = (low + high) >> 1;
	makeTree( idx << 1, low, mid );
	makeTree( ( idx << 1 ) | 1, mid + 1, high );

	T[idx] = min( T[idx << 1], T[(idx << 1 ) | 1] );
}

int queryTree( int idx, int low, int high, int x, int y ) {
	if( x <= low && high <= y ) return T[idx];
	int res = inf, mid = (low + high) >> 1;
	if( x <= mid ) res = queryTree( idx << 1, low, mid, x, y );
	if( y > mid  ) res = min( res, queryTree( ( idx << 1 ) | 1, mid + 1, high, x, y ) );
	return res;
}

int main() {
	double cl = clock();

	while( scanf("%d %d", &n, &q) == 2 && n ) {
		for( int i = 1; i <= n; i++ ) scanf("%d", &A[i]);

		makeTree( 1, 1, n );
		test = 0;

		while( q-- ) {
			char a[40];
			scanf("%s", a);

			if( a[0] == 'q' ) {
				int x, y;
				sscanf( a + 6, "%d , %d", &x, &y );
				printf("%d\n", queryTree( 1, 1, n, x, y ));
			}
			else {
				char *p = strtok( a + 6, "," );
				int x = 0;
				while( p ) {
					sscanf( p, "%d", &C[x] );
					p = strtok( NULL, "," );
					x++;
				}
				int s = T[ pos[ C[0] ] ];
				for( int i = 1; i < x; i++ ) T[ pos[ C[i-1] ] ] = T[ pos[ C[i] ] ];
				T[ pos[ C[x - 1] ] ] = s;

				++test;

				queue <int> Q;
				for( int i = 0; i < x; i++ ) {
					int idx = pos[ C[i] ] >> 1;
					if( update[idx] < test ) {
						update[idx] = test;
						Q.push( idx );
					}
				}

				while( !Q.empty() ) {
					int idx = Q.front(); Q.pop();

					T[idx] = min( T[idx << 1], T[(idx << 1 ) | 1] );
					if( idx > 1 ) {
						idx >>= 1;
						if( update[idx] < test ) {
							update[idx] = test;
							Q.push( idx );
						}
					}
				}
			}
		}
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}
