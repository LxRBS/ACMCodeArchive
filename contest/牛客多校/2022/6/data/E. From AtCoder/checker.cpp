#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define maxn 505
int n, a[maxn][maxn];
ll aa[maxn][maxn];

bool readAns(InStream& stream) {
  int k = stream.readInt(-1, 1000);
  if (k == -1)
    return false;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      aa[i][j] = a[i][j];
    }
  }
  for (int i = 1; i <= k; i++) {
    int r = stream.readInt(1, n), c = stream.readInt(1, n),
        x = stream.readInt(-1000000000, 1000000000);
    for (int j = 1; j <= n; j++) {
      aa[r][j] += x;
      aa[j][c] -= x;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (aa[i][j] < 0) 
        stream.quitf(_wa, "a[%d][%d] is negative.", i, j);
    }
  }
  return true;
}

int main(int argc, char** argv) {
  registerTestlibCmd(argc, argv);
  n = inf.readInt(1, 501);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = inf.readInt(-1000000, 1000000);
    }
  }
  int ourRes = readAns(ans), yourRes = readAns(ouf);
  if (ourRes && !yourRes) {
    quitf(_wa, "Participant cannot but jury can.");
  } else if (!ourRes && yourRes) {
    quitf(_fail, "Jury cannot but participant can.");
  } else {
    quitf(_ok, "Well done.");
  }
  return 0;
}
