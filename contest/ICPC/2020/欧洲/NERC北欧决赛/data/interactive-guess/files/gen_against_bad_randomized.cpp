#include "testlib.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    int maxn = atoi(argv[1]);
    int maxm = atoi(argv[2]);
    double vbeta = atof(argv[3]);
    int topn = atoi(argv[4]);
    double fracEach = atof(argv[5]);
    double fracEach2 = atof(argv[6]);
    double decayPow = atof(argv[7]);
    int n = rnd.next(max(1, maxn * 9 / 10), maxn);
    int m = rnd.next(max(1, maxm * 9 / 10), maxm);

    vector<int> decayTime(n);
    for (int i = 0; i < 1; ++i) {
      decayTime[i] = m;
    }
    for (int i = 1; i < n; ++i) {
      decayTime[i] = round(m * pow(rnd.next(1.0), decayPow));
    }
    shuffle(decayTime.begin(), decayTime.end());

    vector<double> w(m + 1);
    w[0] = 1;
    for (int i = 1; i < topn && i < w.size(); ++i) {
      w[i] = w[i - 1] * vbeta;
    }
    vector<int> score(n);

    cout << n << " " << m << endl;
    for (int step = 0; step < m; ++step) {
      int a = rnd.next(0, 1);
      vector<int> answers(n, a);
      int mn = (int) 1e9;
      for (int i = 0; i < n; ++i) {
        if (step < decayTime[i]) {
          mn = min(mn, score[i]);
        }
      }
      vector<pair<double, int>> candidates;
      double tw = 0;
      for (int i = 0; i < n; ++i) {
        if (step < decayTime[i]) {
          double cw = w[score[i] - mn];
          if (cw > 0) {
            candidates.emplace_back(log(rnd.next(1.0)) * cw, i);
          }
          tw += cw;
        } else {
          if (rnd.next(1.0) < fracEach) {
            answers[i] = 1 - a;
          }
        }
      }
      sort(candidates.begin(), candidates.end());
      if (rnd.next(0, 1) == 0) {
        tw *= fracEach;
      } else {
        tw *= fracEach2;
      }
      for (const auto& c : candidates) {
        answers[c.second] = 1 - a;
        tw -= w[score[c.second] - mn];
        score[c.second] += 1;
        if (tw < 0) break;
      }
      assert(tw < 0);
      for (int x : answers) {
        cout << x;
      }
      cout << " " << a << endl;
    }
    return 0;
}