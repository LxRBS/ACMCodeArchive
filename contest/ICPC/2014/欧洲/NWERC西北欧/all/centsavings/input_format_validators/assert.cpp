#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define ROUND(x) ((((x)+5)/10)*10)

int I, D, prices;

int main() {
	cin >> I >> D;
	assert(0 < I && I <= 2000);
	assert(0 < D && D <= 20);
	FOR(i, 0, I) {
		cin >> prices;
		assert(0 < prices && prices <= 10000);
	}
	return 42;
}
