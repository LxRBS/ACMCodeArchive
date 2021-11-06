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
#include <cmath>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>

using namespace std;

typedef long long LL;

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

int n;
double ans = 0, x;
vector<double> l,r;

int main() {
  ios_base::sync_with_stdio(0);
  cin >> n;
  FOR(i, n) {
    cin >> x;
    l.push_back(x);
    cin >> x;
    r.push_back(x);
  }
  double n2 = 1.0 / n / n;
  FOR(i, n) {
    for (int j = i+1; j < n; j++) {
      if (l[j] <= r[i]) {
        x = (l[j] - l[i]) * (r[j] - l[j]) * (r[j] - l[i]) / 2 +
          (r[i] - l[j]) * (r[j] - r[i]) * (r[j] - l[j]) / 2 +
          (r[i] - l[j]) * (r[i] - l[j]) * (r[i] - l[j]) / 3;
        x /= (r[j] - l[j]);
        x /= (r[i] - l[i]);
        ans += x * n2;
      } else {
        ans += n2 * (r[j] + l[j] - l[i] - r[i]) / 2;
      }
    }
  }
  cout << fixed << setprecision(9) << ans << endl;
  return 0;
}



