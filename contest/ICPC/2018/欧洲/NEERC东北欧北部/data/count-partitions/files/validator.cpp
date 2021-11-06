#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int const MAX_N = 200000;
int const MAX_T = 10000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int tests = inf.readInt(1, MAX_T, "t");
    inf.readEoln();
    for (int i = 0; i < tests; i++) {
        int n = inf.readInt(1, MAX_N, format("n[%d]", i + 1));
        inf.readEoln();
    }
    inf.readEof();
}