#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);

	int p = inf.readInt(1, 100, "p");
    inf.readEoln();
    bool haveS = false;
	for (int i = 0; i < p; ++i) {
		string l = inf.readToken("[A-Z]", "lhs");
		if (l == "S") {
		    haveS = true;
		}
		inf.readSpace();
		inf.readToken("->", "->");
		inf.readSpace();
		inf.readToken("[A-Z]{2}|[a-z]", "rhs");
	    inf.readEoln();
	}
	if (!haveS) {
	    quitf(_fail, "no rules for S");
	}

	int n = inf.readInt(1, 26, "n");
	inf.readSpace();
	int m = inf.readInt(0, n * n, "m");
	inf.readSpace();
	int s = inf.readInt(1, n, "s");
	inf.readSpace();
	int t = inf.readInt(1, n, "t");
	inf.readEoln();

	set<pair<int, int>> edges;
	for (int i = 0; i < m; ++i) {
		int u = inf.readInt(1, n, "u");
		inf.readSpace();
		int v = inf.readInt(1, n, "v");
		inf.readSpace();
		inf.readToken("[a-z]", "x");
		inf.readEoln();
		ensuref(edges.count({u, v}) == 0, "Duplicated edge!");
		edges.insert({u, v});
	}
	inf.readEof();
}
