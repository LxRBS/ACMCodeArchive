#include "testlib.h"

using namespace std;

int main(int argc, char **argv) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, 1000, "n");
  inf.readEoln();
  vector<int> v = inf.readInts(2 * n, 1, 2 * n, "a");
  inf.readEoln();
  inf.readEof();
  sort(v.begin(), v.end());
  for (int i = 0; i < n; i++) {
    ensure(v[i] == i + 1);
  }
  return 0;
}
