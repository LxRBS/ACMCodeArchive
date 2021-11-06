#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int n = inf.readInt(2, 80, "n");
	ensuref(n % 2 == 0, "n=%d is odd", n);
	inf.readSpace();
	inf.readDouble(0, 2 * n, "x");
	inf.readSpace();
	inf.readDouble(0, 2 * n, "y");
	inf.readEoln();
	inf.readEof();
}
