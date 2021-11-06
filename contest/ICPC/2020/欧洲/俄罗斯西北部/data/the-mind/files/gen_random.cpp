#include "testlib.h"
#include <unordered_set>

using namespace std;

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	int n = atoi(argv[1]);
	int maxc = atoi(argv[2]);
	unordered_set<int> used;
	cout << n << '\n';
	for (int i = 0; i < n; i++) {
		if (i > 0) cout << ' ';
		int x;
		do {
			x = rnd.next(1, maxc);
		} while (!used.insert(x).second);
		cout << x;
	}
	cout << '\n';
}
