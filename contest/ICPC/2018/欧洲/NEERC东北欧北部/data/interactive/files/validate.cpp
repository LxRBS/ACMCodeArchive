#include "testlib.h"

using namespace std;

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  inf.readInt(787788, 787788, "787788");
  inf.readEoln();
  int n = inf.readInt(1, 1000, "n");
  inf.readEoln();
  for (int i = 0; i < n; i++) {
    int k = inf.readInt(1, 10, "k[" + vtos(i) + "]");
    vector<int> v(k);
    for (int j = 0; j < k; j++) {
      inf.readSpace();
      v[j] = inf.readInt(-1000, 1000, "a[" + vtos(i) + "][" + vtos(j) + "]");
      ensure(v[j] != 0);
      if (v[j] < 0) v[j] *= -1;
    }
    inf.readEoln();
    sort(v.begin(), v.end());
    ensure(unique(v.begin(), v.end()) == v.end());
  }
  inf.readEof();
  return 0;
}
