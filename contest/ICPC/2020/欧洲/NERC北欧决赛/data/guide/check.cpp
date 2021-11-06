#include "testlib.h"
#include <map>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  int tests = inf.readInt();
  for (int t = 0; t < tests; t++) {
    int n = inf.readInt();
    int k = inf.readInt();
    vector<int> p(n);
    set<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
      p[i] = inf.readInt() - 1;
      edges.insert(make_pair(i, p[i]));
      edges.insert(make_pair(p[i], i));
    }
    int ja = ans.readInt();
    for (int i = 0; i <= ja; i++) {
      ans.readInt();
    }
    int pa = ouf.readInt();

    if (pa != ja) {
      quitf(_wa, "Testcase %d. The length of the participant's path does not equal to jury's path: %d instead of %d", t + 1, pa, ja);
    }

    set<int> total;
    int v = ouf.readInt() - 1;
    if (v != 0) {
      quitf(_wa, "Testcase %d. The starting vertex is not 1", t + 1);
    }
    total.insert(v);
    for (int i = 0; i < pa; i++) {
      int u = ouf.readInt(1, n) - 1;
      total.insert(u);
      if (edges.count(make_pair(v, u)) == 0) {
        quitf(_wa, "Testcase %d. The edge %d-%d does not exist", t + 1, v + 1, u + 1);
      }
      v = u;
    }

    if (total.size() != k) {
      quitf(_wa, "Testcase %d. The total number of visited vertices is %d instead of %d", t + 1, total.size(), k);
    }
  }

  quitf(_ok, "All testcases are passed!");
}