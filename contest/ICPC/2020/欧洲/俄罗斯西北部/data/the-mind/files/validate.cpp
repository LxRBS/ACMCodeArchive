#include "testlib.h"
#include <unordered_set>

using namespace std;

int const N = 100000;
int const X = 1000000000;

int main(int argc, char **argv) {
	registerValidation(argc, argv);
	int n = inf.readInt(3, N, "n");
	inf.readEoln();
	unordered_set<int> v;
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			inf.readSpace();
		}
		int x = inf.readInt(1, X, "a[i]");
		ensuref(v.insert(x).second, "Duplicate cards value = %d", x);
	}
	inf.readEoln();
	inf.readEof();
}
