#include "testlib.h"

using namespace std;

int checkAns(InStream & ouf, int n, vector<int> const &a) {
	long long ans = ouf.readLong(0, (1LL << 31) - 1);
	if (ans == 0) {
		return 0;
	}
	long long last = 0;
	long long prelast = -1;
	for (int i : a) {
		if (last + ans < i) {
			ouf.quitf(_wa, "[n = %d] Can't place all the cards, d = %d", n, (int) ans);
		}
		if (prelast != -1 && prelast + ans >= i) {
			ouf.quitf(_wa, "[n = %d] Ambiguous move, d = %d", n, (int) ans);
		}
		prelast = last;
		last = i;
	}
	return (int) ans;
}

int main(int argc, char **argv) {
	registerTestlibCmd(argc, argv);
	int n = inf.readInt();
	vector<int> a = inf.readInts(n);
	sort(a.begin(), a.end());
	int pa = checkAns(ouf, n, a);
	int ja = checkAns(ans, n, a);
	if ((pa > 0) == (ja > 0)) {
		if (pa > 0) {
			quitf(_ok, "[n = %d] Participant found %d", n, pa);
		} else {
			quitf(_ok, "[n = %d] No solution", n);
		}
	} else if (pa == 0) {
		quitf(_wa, "[n = %d] No solution found, but it exists", n);
	} else {
		quitf(_fail, "[n = %d] Participant found solution, but jury didn't", n);
	}
}
