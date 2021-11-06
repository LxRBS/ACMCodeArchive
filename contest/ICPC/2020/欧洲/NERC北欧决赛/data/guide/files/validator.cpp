#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int MAX_TESTS = 100;
int MAX_N = 100;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int tests = inf.readInt(1, MAX_TESTS, "tests");
  inf.readEoln();
  int total = 0;
  for (int i = 0; i < tests; i++) {
    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();
    for (int j = 1; j < n; j++) {
      if (j != 1) {
        inf.readSpace();
      }
      inf.readInt(1, j, "p");
    }
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}