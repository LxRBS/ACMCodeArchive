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

const ll INF = (ll)2E14;
#define MAXN 200005

int endOne[MAXN], a[MAXN];
int main() {
	int n;
	cin >> n;
	REP(i, 0, n) cin >> a[i];
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] == 1) endOne[i] = max(i, endOne[i + 1]);
		else endOne[i] = -1;
	}
	ll ans = 0;
	REP(i, 0, n) {
		ll sum = a[i], prod = a[i];
		REP(j, i+1, n) {
			if (a[j] == 1) {
				int cntOne = endOne[j] - j + 1;
				if (prod > sum && cntOne >= prod - sum) ans++;
				sum += cntOne;
				j = endOne[j];
			} else {
				sum += a[j];
				if (prod > INF / a[j]) break;
				prod *= a[j];

				if (sum == prod) ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}