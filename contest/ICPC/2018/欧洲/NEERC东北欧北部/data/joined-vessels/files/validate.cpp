#include "testlib.h"

using namespace std;

const int MAXN = 200  * 1000;
const int MAXC = 1000 * 1000 * 1000;

int main(int argc, char **argv) {
  registerValidation(argc, argv);

  int n = inf.readInt(2, MAXN, "n");
  inf.readEoln();
  vector<int> h(n - 1);
  for (int i = 0; i < n - 1; i++) {
    if (i) inf.readSpace();
    h[i] = inf.readInt(1, MAXC, "h[" + vtos(i) + "]");
  }
  inf.readEoln();
  sort(h.begin(), h.end());
  ensure(unique(h.begin(), h.end()) == h.end());

  int q = inf.readInt(1, MAXN, "q");
  inf.readEoln();
  for (int i = 0; i < q; i++) {
    int a = inf.readInt(1, n, "a[" + vtos(i) + "]");
    inf.readSpace();
    int b = inf.readInt(1, n, "b[" + vtos(i) + "]");
    inf.readEoln();
    ensure(a != b);
  }

  inf.readEof(); 
  return 0;
}
