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
#include <math.h>
#include <cmath>

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

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void genmax() {
  int n;
  if (true) {
    n = 100000 - (rand() % 10);
  } else {
    n = 5000 - (rand() % 10);    
  }
  cout << n << endl;
  double curl = 10;
  double curr = 5000;
  FOR(i, n) {
    cout << curl << ' ' << curr << endl;
    curl += fRand(0, 0.1);
    curr += fRand(0, 0.1);
    curl = min(curl, curr);
  }
}

void gennoniter() {
  int n;
  if (true) {
    n = 100000 - (rand() % 10);
  } else {
    n = 5000 - (rand() % 10);    
  }
  cout << n << endl;
  double curl = 10;
  FOR(i, n) {
    cout << curl << ' ' << curl + fRand(0, 0.1) << endl;
    curl += 1.1;
  }
}

void genrandom() {
  int n;
  if (true) {
    n = 100000;
  } else {
    n = 5000;
  }
  cout << n << endl;
  double curl = 10;
  double curr = 5000;

  FOR(i, n/2) {
    cout << curl << ' ' << curl + fRand(0, 0.1) << endl;
    curl += 1.1;
  }

  curr = curl + 5000;

  FOR(i, n/2) {
    cout << curl << ' ' << curr << endl;
    curl += fRand(0, 0.1);
    curr += fRand(0, 0.1);
    curl = min(curl, curr);
  }
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(0);
  int test;
  sscanf(argv[1], "%d", &test);

  srand(test);

  if (test < 5) {
    genmax();
  } else if (test < 10) {
    gennoniter();
  } else {
    genrandom();
  }

  return 0;
}


