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


char str[2010][21];

inline int readAndCheckAnswer(InStream& in, int testcase, int n, int m) {
	int result = in.readInt();
	for (int i = 1; i <= n; i++) {
		string ss = in.readToken();
		if (ss.length() != m)
			in.quitf(_wa, "The length of %d-th string is not %d for test case %d", i, m, testcase);
		for (int j = 1; j <= m; j++) {
			str[i][j] = ss[j-1];
			if (ss[j-1] != '.' && ss[j-1] != '*')
				in.quitf(_wa, "Invalid character for test case %d", testcase);
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str[i][j] == '*')
				cnt++;
		}
	}
	if (cnt != result) {
		in.quitf(_wa, "Incorrect number of xing for test case %d", testcase);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (str[i][j] == '*') {
				int tt = 0;
				if (i > 1 && str[i-1][j] == '*') tt++;
				if (i < n && str[i+1][j] == '*') tt++;
				if (j > 1 && str[i][j-1] == '*') tt++;
				if (j < m && str[i][j+1] == '*') tt++;
				if (tt > 0) {
					in.quitf(_wa, "There are conflit seat for test case %d", testcase);
				}
			} else if (str[i][j] == '.') {
				int tt = 0;
				if (i > 1 && str[i-1][j] == '*') tt++;
				if (i < n && str[i+1][j] == '*') tt++;
				if (j > 1 && str[i][j-1] == '*') tt++;
				if (j < m && str[i][j+1] == '*') tt++;
				if (tt == 0) {
					in.quitf(_wa, "There are still available seats for test case %d", testcase);
				}
			}
		}

	return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int testCase = inf.readInt();
		for (int t = 1; t <= testCase; t++) {
			int n = inf.readInt();
			int m = inf.readInt();
      readCase(ouf, _pe, t);
      readCase(ans, _fail, t);

			int ja = readAndCheckAnswer(ans, t, n, m);
			int pa = readAndCheckAnswer(ouf, t, n, m);

			if (pa > ja)
				quitf(_wa, "Jury has the better answer than the participant for test case %d", t);

			/*
			if (pa < ja)
				quitf(_fail, "Pareticipant has the better answer than jury for test case %d", t);
				*/

    }

    quitf(_ok, "%d test cases(s)", testCase);
}

