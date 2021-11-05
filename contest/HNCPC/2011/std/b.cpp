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

bool isImp7( int i ) {
	if( !(i % 7) ) return true;
	while(i) {
		if( i % 10 == 7 ) return true;
		i /= 10;
	}
	return false;
}

int main() {
	double cl = clock();

	int n, m, k;
	while( scanf("%d %d %d", &n, &m, &k) == 3 && n ) {
		int cnt = 0, period = 2 * n - 2;

		if( n == m || m == 1 ) {
			for( int i = m; ; i += period ) if( isImp7( i ) ) {
				cnt++;
				if( cnt == k ) {
					printf("%d\n", i);
					break;
				}
			}
		}
		else {
			int next = 2 - m;
			for( int i = m; ; swap( next, i ) ) {
				next += period;

				if( isImp7( i ) ) {
					cnt++;
					if( cnt == k ) {
						printf("%d\n", i);
						break;
					}
				}
			}
		}
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}
