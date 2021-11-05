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

int cases;

int main() {
	double cl = clock();

	scanf("%d", &cases);
	while( cases-- ) {
		char a[10];
		scanf("%s", a);

		if( strlen(a) > 3 ) puts("3");
		else {
			if( ( a[0] == 'o' ) + ( a[1] == 'n' ) + ( a[2] == 'e' ) >= 2 ) puts("1");
			else puts("2");
		}
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}
