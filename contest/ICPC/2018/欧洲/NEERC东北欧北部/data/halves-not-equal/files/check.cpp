#include "testlib.h"
#include <utility>
using namespace std;

const double EPS = 1.1e-9;

pair<double, double> divide(double v, double a, double b) {
    if (a > b) {
        auto ans = divide(v, b, a);
        swap(ans.first, ans.second);
        return ans;
    }
    if (v < a) {
        return {v / 2, v / 2};
    }
    if (v > b) {
        return {a / 2 + (v - b) / 2, b / 2 + (v - a) / 2}; 
    }
    return {a / 2, v - a / 2};
}

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = inf.readInt();
    }
    int b = inf.readInt();

    vector<double> c(n);
    double sum = 0;
    for (int i = 0; i < n; i++) {
        c[i] = ouf.readDouble();
        if (c[i] < 0) {
            quitf(_wa, "negative part");
        }
        if (c[i] > a[i] + EPS) {
            quitf(_wa, "wife %d gets more than she claims", i);
        }
        sum += c[i];
    }
    if (!doubleCompare(b, sum, EPS)) {
        quitf(_wa, "the sum of parts differs - expected: '%.10lf', found: '%.10lf', error = '%.10lf'", (double) b, sum, doubleDelta(b, sum));
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pair<double, double> f = divide(c[i] + c[j], a[i], a[j]);
            if (!doubleCompare(f.first, c[i], EPS) || !doubleCompare(f.second, c[j], EPS)) {
                quitf(_wa, "the parts of wives %d and %d are incorrect", i, j);
            }
        }
    }

    quitf(_ok, "");
}
