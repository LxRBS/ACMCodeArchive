#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

long long readAns(InStream& stream, int n, const vector<int>& L, const vector<int>& R) {
  long long declared = stream.readLong();
  vector<int> l(n), r(n);
  for (int i = 0; i < n; i++) {
    l[i] = stream.readInt();
    r[i] = stream.readInt();
  }
  long long total = 0;
  for (int i = 0; i < n; i++) {
    if (!(L[i] <= l[i] && l[i] < r[i] && r[i] <= R[i])) {
      stream.quitf(_wa, "segment %d: [%d; %d] is not a subsegment of [%d; %d]", i + 1, l[i], r[i], L[i], R[i]);
    }
    total += r[i] - l[i];
  }
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return l[i] < l[j];
  });
  for (int i = 0; i < n - 1; i++) {
    if (r[order[i]] > l[order[i + 1]]) {
      stream.quitf(_wa, "subsegments %d and %d intersect", order[i] + 1, order[i + 1] + 1);
    }
  }
  if (total != declared) {
    stream.quitf(_wa, "incorrect sum of length: declared %lld, actual %lld", declared, total);
  }
  return declared;
}

int main(int argc, char** argv) {
  setName("checker for problem hard-optimization");
  registerTestlibCmd(argc, argv);
  int n = inf.readInt();
  vector<int> L(n), R(n);
  for (int i = 0; i < n; i++) {
    L[i] = inf.readInt();
    R[i] = inf.readInt();
  }
  long long participant = readAns(ouf, n, L, R);
  long long jury = readAns(ans, n, L, R);
  if (participant < jury) {
    ouf.quitf(_wa, "valid but inoptimal: expected %lld, found %lld", jury, participant);
  }
  if (participant > jury) {
    ans.quitf(_wa, "better than jury: jury answer = %lld, participant answer = %lld", jury, participant);
  }
  quitf(_ok, "ok, n = %d, ans = %lld", n, participant);
  return 0;
}
