// silly timelimit submission without DP
#include <iostream>
#include <algorithm>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define ROUND(x) ((((x)+5)/10)*10)

int I, D, prices[2005], dp[2005][21][2005], pSum[2005];

int rec(int lastDiv, int restDiv, int index) {
	if (index == I) return ROUND(pSum[I] - pSum[lastDiv]); // last item
//	if (dp[lastDiv][restDiv][index] != 0) return dp[lastDiv][restDiv][index] - 1; // table lookup
	int best = pSum[I] + 10; // INF
	if (restDiv > 0) best = ROUND(pSum[index] - pSum[lastDiv]) + rec(index, restDiv - 1, index + 1); // place divider if possible
	best = min(best, rec(lastDiv, restDiv, index + 1)); // don't place divider
//	dp[lastDiv][restDiv][index] = best + 1; // table store
	return best;
}

int main() {
	cin >> I >> D;
	FOR(i, 0, I) cin >> prices[i];
	FOR(i, 0, I) pSum[i+1] = prices[i] + pSum[i]; // partial sums
	cout << rec(0, D, 0) << endl;
	return 0;
}
