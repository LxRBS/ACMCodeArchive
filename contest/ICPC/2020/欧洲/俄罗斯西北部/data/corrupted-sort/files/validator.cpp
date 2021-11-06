#include "testlib.h"

const int MIN_N = 2;
const int MAX_N = 50;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int n = inf.readInt(MIN_N, MAX_N, "n");
  inf.readEoln();
  std::vector<int> cards(n);
  for (int i = 0; i < n; i++) {
    cards[i] = inf.readInt(1, n, format("card[%d]", i));
    if (i == n - 1) {
      inf.readEoln();
    } else {
      inf.readSpace();
    }
  }
  std::sort(cards.begin(), cards.end());
  for (int i = 0; i < cards.size(); i++) {
    ensuref(cards[i] == i + 1, "%d-th sorted number is not %d (%d)", i + 1, i + 1, cards[i]);
  }
  inf.readEof();
}
