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

struct Card {
	int a[4];
};
Card card[300];
char str[100];
bool isSet(int x, int y, int z) {
	if (x == y || x == z || y == z) return false;
	for (int i = 0; i < 4; i++) {
		int wild_num = 0;
		set<int> st;
		if (card[x].a[i] == -1) wild_num++;
		else st.insert(card[x].a[i]);
		if (card[y].a[i] == -1) wild_num++;
		else st.insert(card[y].a[i]);
		if (card[z].a[i] == -1) wild_num++;
		else st.insert(card[z].a[i]);
		if (st.size() != 1 && st.size() + wild_num != 3)
			return false;
	}

	return true;
}
void check(int testCase) {
	map<string, pair<int, int>> cardIndex;
	cardIndex["one"] = make_pair(0, 0);
	cardIndex["two"] = make_pair(0, 1);
	cardIndex["three"] = make_pair(0, 2);
	cardIndex["diamond"] = make_pair(1, 0);
	cardIndex["squiggle"] = make_pair(1, 1);
	cardIndex["oval"] = make_pair(1, 2);
	cardIndex["solid"] = make_pair(2, 0);
	cardIndex["striped"] = make_pair(2, 1);
	cardIndex["open"] = make_pair(2, 2);
	cardIndex["red"] = make_pair(3, 0);
	cardIndex["green"] = make_pair(3, 1);
	cardIndex["purple"] = make_pair(3, 2);

	int n = inf.readInt();
	for (int i = 1; i <= n; i++) {
		string s = inf.readToken();
		int len = s.length();
		int id = 0;
		for (int j = 0; j < 4; j++) {
			if (s[id] == '[') id++;
			string ss = "";
			while (s[id] != ']') {
				ss = ss + s[id];
				id++;
			}
			if (s[id] == ']') id++;
			if (ss == "*") card[i].a[j] = -1;
			else {
				pair<int, int> pp = cardIndex[ss];
				card[i].a[pp.first] = pp.second;
			}
		}
	}

	int j1, j2, j3;
	int p1, p2, p3;

	p1 = ouf.readInt(-1, n);
	if (p1 == 0) {
		quitf(_wa, "The output of %d test case if invalid", testCase);
	}
	if (p1 != -1) {
		p2 = ouf.readInt(1, n);
		p3 = ouf.readInt(1, n);
	}

	j1 = ans.readInt(-1, n);
	if (j1 != -1) {
		j2 = ans.readInt(1, n);
		j3 = ans.readInt(1, n);
	}

	if (j1 == -1) {
		if (p1 == -1) {
		} else {
			quitf(_wa, "expected no set for test case %d", testCase);
		}
	} else {
		if (p1 == -1) {
			quitf(_wa, "expected has set for test case %d", testCase);
		} else {
			if (isSet(p1, p2, p3)) {
			} else {
				quitf(_wa, "invalid set for test case %d", testCase);
			}
		}
	}
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int testCase = inf.readInt();
		for (int t = 1; t <= testCase; t++) {
        readCase(ouf, _pe, t);
        readCase(ans, _fail, t);
        check(t);
    }

    quitf(_ok, "%d test cases(s)", testCase);
}

