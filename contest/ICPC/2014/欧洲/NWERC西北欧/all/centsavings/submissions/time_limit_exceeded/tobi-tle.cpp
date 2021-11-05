// not so silly tle solution
#include <iostream>
#include <algorithm>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define ROUND(x) ((((x)+5)/10)*10)

int I, D, prices[2005], dp[2005][21][2005];

int rec(int lastDiv, int restDiv, int index) {
	if (index == I) {
		int ret = 0;
		for (int i = lastDiv; i < I; i++) ret += prices[i]; // last item
		return ROUND(ret);
	}
	if (dp[lastDiv][restDiv][index] != 0) return dp[lastDiv][restDiv][index] - 1; // table lookup
	int best = 10000*2005 + 15; // INF
	int sum = 0;
	for (int i = lastDiv; i < index; i++) sum += prices[i];
	if (restDiv > 0) best = ROUND(sum) + rec(index, restDiv - 1, index + 1); // place divider if possible
	best = min(best, rec(lastDiv, restDiv, index + 1)); // don't place divider
	dp[lastDiv][restDiv][index] = best + 1; // table store
	return best;
}

int main() {
	cin >> I >> D;
	FOR(i, 0, I) cin >> prices[i];
	cout << rec(0, D, 0) << endl;
	return 0;
}
