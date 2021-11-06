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
#include <assert.h>

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
  ios_base::sync_with_stdio(0);
  int n;
  int x;
  long double y;
  vector<pair<int, double> > a;
  cin >> n;
  FOR(i, n) {
    cin >> x >> y;
    a.push_back(MP(x, y));
  }
  sort(ALL(a));
  double ans = 0;
  FOR(i, n-1) {
    assert(a[i+1].first != a[i].first);
    ans = max(ans, abs(a[i+1].second  - a[i].second) / abs(a[i+1].first - a[i].first));
  }
  cout << fixed << setprecision(9) << ans << endl;
  return 0;
}

