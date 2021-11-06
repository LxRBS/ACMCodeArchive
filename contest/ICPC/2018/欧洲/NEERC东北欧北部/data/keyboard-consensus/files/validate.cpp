#include "testlib.h"

using namespace std;

void readPerm(int n) {
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    v[i] = inf.readInt(1, n, "v[" + vtos(i) + "]");
    if (i != n - 1) inf.readSpace();
  }
  inf.readEoln();
  sort(v.begin(), v.end());
  ensure(unique(v.begin(), v.end()) == v.end());
}

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int n = inf.readInt(2, 100, "n");
  inf.readEoln();
  readPerm(n);
  readPerm(n);
  inf.readEof();
  return 0;
}
