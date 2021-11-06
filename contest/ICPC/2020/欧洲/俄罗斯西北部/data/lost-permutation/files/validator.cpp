#include "testlib.h"

using namespace std;

int const MAX_N = 10000;

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int tests = inf.readInt(1, MAX_N, "t");
  inf.readEoln();
  int sumN = 0;
  for (int i = 0; i < tests; i++) {
    int n = inf.readInt(3, MAX_N, format("n[%d]", i));
    sumN += n;
    ensuref(sumN <= MAX_N, "Sum of n's exceeds maximum: %d > %d", sumN, MAX_N);
    vector<int> pi(n);
    vector<bool> used(n);
    for (int j = 0; j < n; j++) {
      inf.readSpace();
      pi[j] = inf.readInt(1, n, format("pi[%d][%d]", i, j));
      pi[j]--;
      ensure(!used[pi[j]]);
      used[pi[j]] = true;
    }
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
