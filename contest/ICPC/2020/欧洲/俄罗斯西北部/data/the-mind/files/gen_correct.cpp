#include "testlib.h"
#include <unordered_set>
#include <cassert>

using namespace std;

int const MAXC = 1000000000;

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	int n = atoi(argv[1]);
	int from = atoi(argv[2]);
	int to = atoi(argv[3]);
	assert(2 * from > to);
	assert((long long) from * n <= MAXC);
	int current = 0;
	int lastDiff = to;
	int minDiff = max(1, to + 1 - from);
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		int curDiff = rnd.next(max(minDiff, to + 1 - lastDiff), from);
		current += curDiff;
		a[i] = current;
		lastDiff = curDiff;
	}
	shuffle(a.begin(), a.end());
	cout << n << '\n';
	for (int i = 0; i < n; i++) {
		if (i > 0) cout << ' ';
		cout << a[i];
	}
	cout << '\n';
}
