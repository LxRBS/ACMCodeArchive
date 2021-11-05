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

int grundy( int n ) {
	if( n == 1 ) return 0;
	if( n & 1 ) return grundy( n/2 );
	return n/2;
}

int main() {
	double cl = clock();

	int n;
	while( scanf("%d", &n) == 1 && n ) {
		printf("%s\n", grundy(n) ? "Alice" : "Bob");
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}
