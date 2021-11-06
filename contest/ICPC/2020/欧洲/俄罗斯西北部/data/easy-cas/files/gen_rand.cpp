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
  int successes = opt<int>("successes");
  int C = rnd.next(maxC) + 1;
  cout << n << " " << C << endl;
  vector<Cas> test;
  for (int i = 0; i < n - successes; i++) {
      int a = rnd.next(maxC) + 1;
      int b = rnd.next(maxC) + 1;
      test.push_back(Cas(a, b, 0));
  }
  for (int i = 0; i < successes; i++) {
      int b = rnd.next(maxC) + 1;
      test.push_back(Cas(C, b, 1));
      C = b;
  }
  shuffle(test.begin(), test.end());
  for (auto cas : test) {
      cout << cas.a << " " << cas.b << " " << cas.s << endl;
  }

}
