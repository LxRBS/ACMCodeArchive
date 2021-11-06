#include "testlib.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    int maxn = atoi(argv[1]);
    int maxm = atoi(argv[2]);
    int oneSize = atoi(argv[3]);
    int cycles = atoi(argv[4]);
    int n = rnd.next(max(1, maxn * 9 / 10), maxn);
    int m = rnd.next(max(1, maxm * 9 / 10), maxm);
    assert(oneSize * cycles <= m);

    vector<vector<int>> answers(m, vector<int>(n));
    vector<int> realAnswers(m);
    for (int step = 0; step < m; ++step) {
      int a = rnd.next(0, 1);
      realAnswers[step] = a;
      answers[step].assign(n, a);
    }

    for (int ci = 0; ci < cycles; ++ci) {
      int left = ci * m / cycles;
      int right = (ci + 1) * m / cycles;
      assert(oneSize <= right - left);
      for (int i = 0; i < n; ++i) {
        int pos = rnd.next(left, right - oneSize);
        for (int j = pos; j < pos + oneSize; ++j) answers[j][i] = 1 - answers[j][i];
      }
    }

    vector<int> decayTime(n);
    for (int i = 0; i < 1; ++i) {
      decayTime[i] = m;
    }
    for (int i = 1; i < n; ++i) {
      decayTime[i] = rnd.next(0, m);
    }
    shuffle(decayTime.begin(), decayTime.end());
    for (int step = 0; step < m; ++step) {
      for (int i = 0; i < n; ++i) {
        if (decayTime[i] <= step) {
          answers[step][i] = rnd.next(1.0) < 0.8 ? (1 - realAnswers[step]) : realAnswers[step];
        }
      }
    }

    cout << n << " " << m << endl;
    for (int step = 0; step < m; ++step) {
      for (int x : answers[step]) cout << x;
      cout << " " << realAnswers[step] << endl;
    }
    return 0;
}