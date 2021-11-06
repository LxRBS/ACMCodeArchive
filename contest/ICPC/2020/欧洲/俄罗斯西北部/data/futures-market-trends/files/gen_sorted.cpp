#include "testlib.h"

using namespace std;

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);

  int m = opt<int>("min");
  int M = opt<int>("max");
  int step = opt<int>("step");
  string dir = opt<string>("dir");
  double C = opt<double>("C");
  int n = (M - m) / step + 1;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = i * step + m;
  }
  if (dir == "desc") {
    reverse(a.begin(), a.end());
  }
  printf("%d %.9lf\n", n, C);
  for (int i = 0; i < n; i++) {
    printf("%d%c", a[i], " \n"[i == n - 1]);
  }
}
