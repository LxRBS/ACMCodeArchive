#include "testlib.h"
#include <cstdio>
#include <set>

using namespace std;

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int n = atoi(argv[1]);
  int c = atoi(argv[2]);
  int q = atoi(argv[3]);
  printf("%d\n", n);

  set<int> s;
  vector<int> hs;
  for (int i = 0; i < n - 1; i++) {
    int h;
    do {
      h = rnd.next(1, c);
    } while (s.count(h));
    s.insert(h);
    hs.push_back(h);
  }
  if (argc > 4 && !strcmp(argv[4], "inc")) {
    sort(hs.begin(), hs.end());
  } else if (argc > 4 && !strcmp(argv[4], "dec")) {
    sort(hs.rbegin(), hs.rend());
  }
  if (argc > 5 && !strcmp(argv[5], "noise")) {
    int times = atoi(argv[6]);
    for (int i = 0; i < times; i++) {
      int a = rnd.next(n - 1);
      int b = rnd.next(n - 1);
      swap(hs[a], hs[b]);
    }
  }
  for (int i = 0; i < n - 1; i++) {
    printf("%d%c", hs[i], " \n"[i == n - 2]);
  }

  printf("%d\n", q);
  if (q >= n * 1LL * (n - 1)) {
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i != j) {
          v.emplace_back(i, j);
        }
      }
    }
    shuffle(v.begin(), v.end());
    for (auto x : v) {
      printf("%d %d\n", x.first + 1, x.second + 1);
    }
    q -= n * (n - 1);
  }
  for (int i = 0; i < q; i++) {
    int a, b;
    do {
      a = rnd.next(1, n);
      b = rnd.next(1, n);
    } while (a == b);
    printf("%d %d\n", a, b);
  }

}
