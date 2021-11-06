#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int const MAX_X = (int) 1e8;

int readAns(InStream& ouf, int d, vector<int>& masks) {
	int ops = ouf.readInt(0, (d + 1) * (1 << d));
	int curMask = 0;
	vector<bool> visited(1 << d);
	for (int i = 0; i < ops; i++) {
		string action = ouf.readToken(format("[0-%dR]", d - 1));
		if (action == "R") {
			curMask = 0;
		} else {
			curMask |= 1 << (action[0] - '0');
			visited[curMask] = true;
		}
	}
	for (size_t i = 0; i < masks.size(); i++) {
		if (!visited[masks[i]]) {
			string mbin;
			for (int bit = 0; bit < d; bit++) {
				mbin += (char) ('0' + ((masks[i] >> bit) & 1)); 
			}
			ouf.quitf(_wa, "Did not visit the %d-th mask %s", (int)i, mbin.c_str());
		}
	}
	return ops;
}


int main(int argc, char* argv[]) {

    registerTestlibCmd(argc, argv);
    int d = inf.readInt();
	int n = inf.readInt();
	vector<int> masks(n);
	for (int i = 0; i < n; i++) {
		string s = inf.readToken();
		for (int j = 0; j < d; j++) {
			masks[i] |= (s[j] - '0') << j;
		}
	}
	int juryAns = readAns(ans, d, masks);
	int partAns = readAns(ouf, d, masks);
	if (partAns < juryAns) {
		quitf(_fail, "FAIL, participant found better solution: %d < %d | d = %d, n = %d", partAns, juryAns, d, n);
	} else if (partAns > juryAns) {
		quitf(_wa, "WA, jury found better solution: %d > %d | d = %d, n = %d", partAns, juryAns, d, n);
	} else {
		quitf(_ok, "OK, d = %d, n = %d, ans = %d", d, n, juryAns);
	}
}