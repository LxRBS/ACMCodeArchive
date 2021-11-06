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

int main() {
  int n;
  long double x,y;
  vector<pair<long double, long double> > a;
  cin >> n;
  if (n < 2 || n > 200000) {
    cout << "BAD n" << endl;
    return 0;
  }
  FOR(i, n) {
    cin >> x >> y;
    a.push_back(MP(x, y));
    if (x < -1000000000 || x > 1000000000) {
      cout << "BAD x" << endl;
      return 0;
    }
    if (y < -1000000000 || y > 1000000000) {
      cout << "BAD y" << endl;
      return 0;
    }
  }
  sort(ALL(a));
  long double ans = 0, ans1 = 0;;
  FOR(i, n-1) {
    ans = max(ans, abs(a[i+1].second  - a[i].second) / abs(a[i+1].first - a[i].first));
  }
  if (n < 2000) {
    // Do a brute-force check for small n's
    FOR(i, n) FOR(j, n) if (i != j) ans1 = max(ans1, abs(a[i].second  - a[j].second) / abs(a[i].first - a[j].first));
    if (abs(ans - ans1) > 0.000000001) {
      cout << "BAD ANS" << endl;
      return 0;
    }
  }
  return 42;
}
