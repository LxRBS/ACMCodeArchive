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

double outside_expectation = 0;
double psum[4];

int main() {
  ios_base::sync_with_stdio(0);
  cin >> n;
  FOR(i, n) {
    cin >> x;
    l.push_back(x);
    cin >> x;
    r.push_back(x);
  }

  if (n <= 1) {
    cout << 0 << endl;
    return 0;
  }

  int idx = 0; // points to largest index that intersects with current range
  double n2 = 1.0 / n / n;

  outside_expectation += (l[0] + r[0]) / 2;
  if (r[0] - l[0]) {
    psum[0] = r[0] * r[0] * r[0] / (r[0] - l[0]) / 3;
    psum[1] = r[0] * r[0] / (r[0] - l[0]);
    psum[2] = r[0] / (r[0] - l[0]);
    psum[3] = 1.0 / (r[0] - l[0]) / 3;
  }

  for (int i = 1; i < n; i++) {
    // Update idx value
    while (idx < i && r[idx] <= l[i]) {
      // Remove
      if (r[idx] - l[idx]) {
        psum[0] -= r[idx] * r[idx] * r[idx] / (r[idx] - l[idx]) / 3;
        psum[1] -= r[idx] * r[idx] / (r[idx] - l[idx]);
        psum[2] -= r[idx] / (r[idx] - l[idx]);
        psum[3] -= 1.0 / (r[idx] - l[idx]) / 3;
      }

      idx++;
    }

    // Add answer for shit outside of the range
    ans += (i * (l[i] + r[i]) / 2 - outside_expectation) * n2;

    // Tough value
    if (r[i] - l[i]) {
      ans += psum[0] / (r[i] - l[i]) * n2;
      ans -= psum[1] / (r[i] - l[i]) * l[i] * n2;
      ans += psum[2] / (r[i] - l[i]) * l[i] * l[i] * n2;
      ans -= psum[3] / (r[i] - l[i]) * l[i] * l[i] * l[i] * n2;
    }

    // Update
    outside_expectation += (l[i] + r[i]) / 2;
    if (r[i] - l[i]) {
      psum[0] += r[i] * r[i] * r[i] / (r[i] - l[i]) / 3;
      psum[1] += r[i] * r[i] / (r[i] - l[i]);
      psum[2] += r[i] / (r[i] - l[i]);
      psum[3] += 1.0 / (r[i] - l[i]) / 3;
    }
  }

  cout << fixed << setprecision(9) << ans << endl;
  return 0;
}



