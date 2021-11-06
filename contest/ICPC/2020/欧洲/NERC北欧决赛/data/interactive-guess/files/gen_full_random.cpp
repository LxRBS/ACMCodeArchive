#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    int maxn = atoi(argv[1]);
    int maxm = atoi(argv[2]);
    double min_prob = atof(argv[3]);
    double max_prob = atof(argv[4]);
    int n, m;
    if (maxn == 1 || maxm == 1) {
      n = maxn;
      m = maxm;
    } else {
      n = rnd.next(max(1, maxn * 9 / 10), maxn);
      m = rnd.next(max(1, maxm * 9 / 10), maxm);
    }
    vector<double> probs(n);
    for (double& x : probs) x = rnd.next(1.0) * (max_prob - min_prob) + min_prob;
    cout << n << " " << m << endl;
    for (int step = 0; step < m; ++step) {
      int a = rnd.next(0, 1);
      for (double p : probs) if (rnd.next(1.0) < p) {
        cout << 1 - a;
      } else {
        cout << a;
      }
      cout << " " << a << endl;
    }
    return 0;
}