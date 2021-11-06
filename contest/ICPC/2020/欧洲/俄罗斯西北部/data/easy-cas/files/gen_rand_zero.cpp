#include "testlib.h"

using namespace std;

struct Cas {
    int a, b, s;

    Cas(int a, int b, int s) : a(a), b(b), s(s)
    { }
};

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n");
  int maxC = opt<int>("maxc");
  int bad = opt<int>("bad");
  int C = rnd.next(maxC) + 1;
  cout << n << " " << C << endl;
  vector<Cas> test;
  for (int i = 0; i < n; i++) {
      int a;
      do {
          a = rnd.next(maxC) + 1;
      } while (a == C);
      int b;
      do {
          b = rnd.next(maxC) + 1;
      } while (b == C);
      test.push_back(Cas(a, b, i < bad));
  }

  shuffle(test.begin(), test.end());
  for (auto cas : test) {
      cout << cas.a << " " << cas.b << " " << cas.s << endl;
  }

}
