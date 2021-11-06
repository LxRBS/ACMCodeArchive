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
  int successes = opt<int>("successes");
  vector<int> order;
  for (int i = 0; i < n + 1; i++) {
      order.push_back(i + 1);
  }
  shuffle(order.begin(), order.end());
  int C = order[0];
  cout << n << " " << C << endl;
  vector<Cas> test;
  for (int i = 0; i < successes; i++) {
      test.push_back(Cas(order[i], order[i+1], 1));
  }
  for (int i = 0; i < n - successes; i++) {
      int a = rnd.next(n) + 1;
      int b = rnd.next(n) + 1;
      test.push_back(Cas(a, b, 0));
  }
  shuffle(test.begin(), test.end());
  for (auto cas : test) {
      cout << cas.a << " " << cas.b << " " << cas.s << endl;
  }

}
