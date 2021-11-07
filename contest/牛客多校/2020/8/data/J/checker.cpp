#include <bits/stdc++.h>
#include <iostream>
#include "testlib.h"
using namespace std;

string getStringFromInt(int a) {
	string ss = "";
	do {
		ss = (char)('0' + a%10) + ss;
		a /= 10;
	} while (a);
	return ss;
}

void readCase(InStream& in, TResult pe, int testCase) {
    string caseStr = in.readToken();
    if (caseStr != "Case") {
        in.quitf(pe, "Expected 'Case' but found '%s' [test case %d]", compress(caseStr).c_str(), testCase);
    }

    string numExpStr = "#" + getStringFromInt(testCase) + ":";
    string numStr = in.readToken();
    if (numExpStr != numStr)
        in.quitf(pe, "Expected '%s' but found '%s' [test case %d]", compress(numExpStr).c_str(), compress(numStr).c_str(), testCase);
}

void check(int testCase, double EPS) {

	vector<pair<int, int>> vec;
	int n = inf.readInt();
	for (int i = 0; i < n; i++) {
		int l = inf.readInt();
		int r = inf.readInt();
		vec.push_back(make_pair(l, r));
	}
	vector<pair<double, double>> tmp;
	for (int i = 0; i < n; i++) {
		double x, y;
		x = ouf.readDouble(i+1, i+1);
		y = ouf.readDouble(vec[i].first, vec[i].second);
		tmp.push_back(make_pair(x, y));
		if (x != i+1 || y < vec[i].first || y > vec[i].second) {
			quitf(_wa, "The %d-th point is not belong to the segment %d", i+1, i+1);
		}
	}
	double p = 0;
	for (int i = 1; i < n; i++) {
		p += sqrt((tmp[i].first-tmp[i-1].first)*(tmp[i].first-tmp[i-1].first) 
				+ (tmp[i].second-tmp[i-1].second)*(tmp[i].second-tmp[i-1].second));
	}
	tmp.clear();
	for (int i = 0; i < n; i++) {
		double x, y;
		x = ans.readDouble(i+1, i+1);
		y = ans.readDouble(vec[i].first, vec[i].second);
		tmp.push_back(make_pair(x, y));
	}
	double j = 0;
	for (int i = 1; i < n; i++) {
		j += sqrt((tmp[i].first-tmp[i-1].first)*(tmp[i].first-tmp[i-1].first) 
				+ (tmp[i].second-tmp[i-1].second)*(tmp[i].second-tmp[i-1].second));
	}
	if (!doubleCompare(j, p, EPS) && j < p) {
		quitf(_wa, "number differ - expectedf '%.7f', found: '%.7f', error = '%.7f' [test case %d]", j, p, doubleDelta(j, p), testCase);
	}
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int testCase = inf.readInt();
		for (int t = 1; t <= testCase; t++) {
        readCase(ouf, _pe, t);
        readCase(ans, _fail, t);
        check(t, 1E-6);
    }

    quitf(_ok, "%d test cases(s)", testCase);
}

