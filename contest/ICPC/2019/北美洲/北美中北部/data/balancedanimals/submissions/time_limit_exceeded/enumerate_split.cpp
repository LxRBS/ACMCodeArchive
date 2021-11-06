#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <complex>
#include <ctime>
#include <cassert>
#include <functional>

using namespace std;

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

const int INF = (int)1e9;
#define MAXN 200005
#define MAXV 20000

int main() {
	int n;
	cin >> n;
	VI val(n, 0);
	REP(i, 0, n) cin >> val[i];
	REP(v, 1, MAXV+1) {
		int low = 0, high = 0;
		REP(i, 0, n) {
			if (val[i] < v) low += val[i];
			else if (val[i] > v) high += val[i];
		}
		if (low == high) return cout << v << endl, 0;
	}
	return 1;
}