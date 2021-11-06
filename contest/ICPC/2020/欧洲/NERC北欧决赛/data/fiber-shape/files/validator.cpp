#include "testlib.h"
#include <vector>

using namespace std;

int const MAX_N = 10000;
int const MAX_X = 100000;

long long vm(long long x1, long long y1, long long x2, long long y2) {
  return x1 * y2 - x2 * y1;
}

double dist(int x1, int y1, int x2, int y2) {
  double dx = x1 - x2, dy = y1 - y2;
  return sqrt(dx * dx + dy * dy);
}

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int n = inf.readInt(3, MAX_N, "n");
  inf.readSpace();
  int l = inf.readInt(1, 8 * MAX_X, "l");
  inf.readEoln();
  vector<int> x(n), y(n);
	for (int i = 0; i < n; ++i) {
		x[i] = inf.readInt(-MAX_X, MAX_X, format("x[%d]", i));
		inf.readSpace();
		y[i] = inf.readInt(-MAX_X, MAX_X, format("y[%d]", i));
		inf.readEoln();
	}
  double perimeter = 0;
	// doesn't check self-intersections!
	for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n, k = (i + 2) % n;
    ensuref(vm(x[j] - x[i], y[j] - y[i], x[k] - x[i], y[k] - y[i]) > 0, "Vertices %d %d %d form a non-convex triple", i, j, k);
    perimeter += dist(x[i], y[i], x[j], y[j]);
  }
  ensuref(perimeter + 2e-3 < l, "l must be greater than perimeter: l = %.8f, p = %.8f", l, perimeter);
  inf.readEof();
	return 0;
}
