#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

long long MIN = -1e9;
long long MAX = 1e9;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long s = inf.readLong();

    string ja = ans.readWord();
    string pa = ouf.readWord();
    if (pa == "Impossible") {
        if (ja == "Impossible") {
            quitf(_ok, "Impossible");
        } else {
            quitf(_wa, "Jury has the answer but participant has not");
        }
    }
    ouf.reset();
    vector<long long> x(4);
    vector<long long> y(4);
    for (int i = 0; i < 4; i++) {
        x[i] = ouf.readLong(MIN, MAX);
        y[i] = ouf.readLong(MIN, MAX);
    }
    for (int i = 1; i < 4; i++) {
        x[i] -= x[0];
        y[i] -= y[0];
    }
    for (int i = 1; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            long long d1 = x[i] * x[i] + y[i] * y[i];
            long long d2 = x[j] * x[j] + y[j] * y[j];
            if (d1 == d2) {
                long long cp = x[i] * x[j] + y[i] * y[j];
                if (cp == 0) {
                    int k = 1 + 2 + 3 - i - j;
                    if (x[k] == x[i] + x[j] && y[k] == y[i] + y[j]) {
                        if (d1 == s) {
                            quitf(_ok, "");
                        } else {
                            quitf(_wa, "Area is %lld instead of %lld", d1, s);
                        }
                    }
                }
            }
        }
    }
    quitf(_wa, "Not a square");

}