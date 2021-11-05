#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define ROUND(x) ((((x)+5)/10)*10)

int I, D, prices[2005], dp[21], mini;

int main() {
	cin >> I >> D;
	FOR(i, 0, I) cin >> prices[i];
	dp[0] = 0; // cost is zero with 0 divider
	FOR(i, 1, D+1) dp[i] = INT_MAX/2; // you have to place less dividers first
	FOR(i, 0, I) {
		FORD(j, 1, D+1) dp[j] = min(dp[j] + prices[i], ROUND(dp[j - 1] + prices[i])); // either just add item or place divider after item
		dp[0] += prices[i]; // no divider, no choice
	}
	mini = INT_MAX/2;
	FOR(i, 0, D+1) mini = min(mini, dp[i]);
	cout << ROUND(mini) << endl;
	return 0;
}
