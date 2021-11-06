#include "testlib.h"

using namespace std;

int const MAX_K = 30;
int const MAX_M = 100000;

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int k = inf.readInt(1, MAX_K, "k");
  inf.readSpace();
  int n = inf.readInt(0, min((1 << k) - 1, MAX_M), "n");
  inf.readEoln();

  set<pair<int, int>> viewed;
  for (int i = 0; i < n; i++) {
    int stage = inf.readInt(1, k, format("s[%d]", i));
    inf.readSpace();
    int match = inf.readInt(1, 1 << (k - stage), format("m[%d]", i));
    inf.readEoln();
    ensuref(viewed.find({stage, match}) == viewed.end(), "Pre-viewed match (%d, %d) appears twice", stage, match);
    viewed.insert({stage, match});
  }
  inf.readEof();
  return 0;
}
