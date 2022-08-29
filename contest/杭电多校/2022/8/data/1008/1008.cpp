//1008, std
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n, m, x, y, dp[N][3];

vector <int> G[N];

void add(int x, int y) {
	G[x].push_back(y);
	G[y].push_back(x);
}

void dfs(int x, int f) {
	dp[x][0] = 0; dp[x][1] = dp[x][2] = 1;
	for(auto V : G[x]) {
		if(V == f) 
		continue;
		dfs(V, x);
		dp[x][0] += max(dp[V][0], max(dp[V][1], dp[V][2]));
		dp[x][2] += dp[V][0]; 
		dp[x][2] = max(dp[x][2], dp[x][1] + dp[V][1]);
		dp[x][1] += dp[V][0];
		dp[x][2] = max(dp[x][2], dp[x][1]);
	}
}

void rmain() {
	scanf("%d", &n);
//	cerr << n << endl;
	for(int i = 1; i <= n; ++ i) {
		memset(dp[i], 0, sizeof(dp[i]));
		G[i].clear();
	}
	for(int i = 1; i < n; ++ i) {
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1, 0);
	cout << max(dp[1][0], max(dp[1][1], dp[1][2])) << endl;
}

int main() {
//	freopen("1008.in", "r", stdin);
//	freopen("1008.out", "w", stdout);

int size(512<<20); 
__asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));
	int T;
	for(cin >> T; T --;) {
		rmain();
	}
	exit(0);
}
