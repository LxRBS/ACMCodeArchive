#include "testlib.h"

using namespace std;

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n");
  int m = opt<int>("min");
  int M = opt<int>("max");
  int res = opt<int>("ans");
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = rnd.next(m, M);
  }
  vector<double> trends;

  vector<int> b = a;
  for (int i = n - 1; i >= 0; i--) {
    a[i] -= a[i-1];
  }
  a.erase(a.begin());
  for (int i = 0; i < (int)a.size(); i++) {
    long long s = a[i], s2 = a[i] * a[i];
    for (int j = i + 1; j < (int)a.size(); j++) {
      s += a[j];
      s2 += a[j] * a[j];
      long long den = (j - i + 1) * s2 - s * s;
      if (s != 0) {
        trends.push_back(abs(s) / sqrt(den));
      }
    }
  }
  trends.push_back(0);
  trends.push_back(1000.0);
  sort(trends.rbegin(), trends.rend());
  if (has_opt("around")) {
    int min_ans = res - opt<int>("around");
    int max_ans = res + opt<int>("around");
    res = min_ans;
    for (int i = min_ans; i < max_ans; i++) {
      if (trends[res] - trends[res+1] < trends[i] - trends[i+1]) {
        res = i;
      }
    }
    fprintf(stderr, "biggest diff = %e\n", trends[res] - trends[res+1]);
  }
  double C = has_opt("C") ? opt<double>("C") : clamp((trends[res] + trends[res + 1]) / 2.0, 0.001, 1000.0);

  printf("%d %.9lf\n", n, C);
  for (int i = 0; i < n; i++) {
    printf("%d%c", b[i], " \n"[i == n - 1]);
  }
}
