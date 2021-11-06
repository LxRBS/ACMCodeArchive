#include <bits/stdc++.h>
using namespace std;

const int N = 2510;
int cost[N][N];

int pred[N];
vector<int> succ[N];
int max_reach[N];

int discount[N];
long long dp[N];

bool is_max_on_cycle(int i) {
	int j = i, max_ancestor = j;
	for (int t = 0; t < N; t++) {
		max_ancestor = max(max_ancestor,j);
		j = pred[j];
	}
	return i == max_ancestor;
}

int main() {
	int n; cin >> n;
	long long base_cost = 0;

	for (int i = 1; i <= n; i++) {
		int min_cost;
		cin >> pred[i] >> min_cost;
		
		succ[pred[i]].push_back(i);
		
		base_cost += min_cost;
		for (int j = 0; j <= n; j++) {
			cin >> cost[i][j];
			cost[i][j] -= min_cost;
		}
	}
	
	iota(max_reach,max_reach+n+1,0);
	for (int t = 0; t < N; t++) {
		for (int i = 0; i <= n; i++) {
			for (int j: succ[i]) {
				max_reach[i] = max(max_reach[i], max_reach[j]);
			}
		}
	}
	
	for (int i = 0; i <= n; i++) {
		if (is_max_on_cycle(i)) {
			discount[i] = cost[i][n];
			for (int j = pred[i]; j != i; j = pred[j]) {
				discount[i] = min(discount[i], cost[j][n]);
			}
			for (int j = pred[i]; j != i; j = pred[j]) {
				discount[j] = discount[i];
			}
			base_cost += discount[i];
		}
	}

	memset(dp,0x3f,sizeof dp);
	dp[max_reach[0]] = base_cost;
	for (int i = 0; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (max_reach[j] > i) {
				dp[max_reach[j]] = min(dp[max_reach[j]], dp[i] + cost[j][i] - discount[j]);
			}
		}
	}
	cout << dp[n] << endl;
}
