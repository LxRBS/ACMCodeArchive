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
string edge[19] = {
  "5 3 5 6",
  "5 300 5 11",
  "5 10 5 10",
  "5 11 5 10",
  "5 19 5 10",
  "5 20 5 10",
  "5 21 5 10",
  "5 20 5 20",
  "9 20 10 20",
  "10 20 10 20",
  "11 20 10 20",
  "10 20 11 20",
  "1 6 1 5",
  "3 1 3 5",
  "0 0 1 1",
  "3 3 1 1",
  "0 0 1 0",
  "0 1 0 0",
  "1 0 0 0",
};

int main(int argc, char* argv[]) {
  sscanf(argv[1], "%d", &test);

  if (test < 19) {
    cout << edge[test] << endl;
    return 0;
  }

  srand(test);
  cout << 1 + (rand() % 1000000) << ' ' <<
          1 + (rand() % 1000000) << ' ' <<
          1 + (rand() % 1000000) << ' ' <<
          1 + (rand() % 1000000) << endl;

  return 0;
}

