#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string.h>
#include <utility>
#include <queue>
#include <stack>
#include <iomanip>
#include <ctype.h>
#include <map>
#include <set>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <sstream>
#include <math.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

#define FOR(i,n) for(int i = 0;i < n;i++)
#define MP make_pair
#define PB push_back
#define ALL(a) (a).begin(),(a).end()
#define PII pair<int, int>
#define PLL pair<long long, long long>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define INF 2000000007
#define y1 uu1
#define y2 uu2
#define hash mash
const double EPS = 1E-12;
const double PI = acos(-1.0);
const LL mod = 1000000007;

using namespace std;

int test;

int main(int argc, char* argv[]) {
  sscanf(argv[1], "%d", &test);
  srand (test);

  int n = 1000 + test;
  long double x,y;
  cout << n << endl;
  set<int> used;
  FOR(i, n) {
    int x = -10000000 + (rand() % 1000000000);

    while (used.find(x) != used.end()) {
      x = -10000000 + (rand() % 1000000000);
    }
    used.insert(x);

    double y = -10000000 + (rand() % 200000000);
    double b = (rand() % 1000);
    cout << fixed << setprecision(6) << x << ' ' << y + b / 1000.0 << endl;
  }
  return 0;
}
