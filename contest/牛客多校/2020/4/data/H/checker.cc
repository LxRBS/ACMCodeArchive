#include "testlib.h"
#include <vector>
#include <algorithm>

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int main(int argc, char** argv) {
  registerTestlibCmd(argc, argv);
  int T = inf.readInt();
  for (int cas = 1; cas <= T; ++cas) {
    int n = inf.readInt();
    int jury_ans = ans.readInt();
    for (int i = 0; i < jury_ans; ++i) {
      ans.readInt(); ans.readInt();
    }
    int user_ans = ouf.readInt();
    if (jury_ans != user_ans) {
      quitf(_wa, "case #%d: expected %d, but %d found.", cas, jury_ans, user_ans);
    }
    int m = jury_ans;
    std::vector<int> a(m), b(m);
    std::vector<bool> mark(n + 1);
    for (int i = 0; i < m; ++i) {
      a[i] = ouf.readInt(1, n, format("a[%d]", i + 1));
      b[i] = ouf.readInt(1, n, format("b[%d]", i + 1));
      if (mark[a[i]]) quitf(_wa, "case #%d: duplicate number %d.", cas, a[i]);
      mark[a[i]] = true;
      if (mark[b[i]]) quitf(_wa, "case #%d: duplicate number %d.", cas, b[i]);
      mark[b[i]] = true;
      if (gcd(a[i], b[i]) == 1) quitf(_wa, "case #%d: gcd(%d, %d) == 1.", cas, a[i], b[i]);
    }
  }
  quitf(_ok, "%d cases.", T);
  return 0;
}
