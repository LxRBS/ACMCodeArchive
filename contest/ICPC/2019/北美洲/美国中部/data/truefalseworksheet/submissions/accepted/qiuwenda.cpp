#include <bits/stdc++.h>
using namespace std;
const int N = 5005, MOD = 1e9 + 7;
int dp[N], hint2[N], hint1[N];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		hint1[i] = i;
		hint2[i] = 0;
	}
	for (int i = 0; i < m; ++ i) {
		int x, l, r;
		std::string s;
		std::cin >> l >> r >> s;
		(s == "same") ? (x=1) : (x=2);
		if (x == 1) {
			hint1[r] = min(hint1[r], l);
		}
		else {
			hint2[r] = max(hint2[r], l);
		}
	}
	dp[0] = 1;
	for (int i = 1; i <= n; ++ i) {
		int h1 = i, h2 = 0;
		for (int j = i; j >= 1; -- j) {
			h2 = max(h2, hint2[j]);
			h1 = min(h1, hint1[j]);
			if (j > h2 && j <= h1) {
				(dp[i] += dp[j - 1]) %= MOD;
			}
		}
	}
	printf("%d\n", (dp[n] * 2) % MOD);
}

