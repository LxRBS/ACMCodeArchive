#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
int n, T = 0;
vector<int> adj[N];
double x[N], y[N];

void dfs(int i, int p = -1) {
	for (int j: adj[i]) {
		if (j == p) continue;

		x[j] = x[i] + cos(T*2*M_PI/n);
		y[j] = y[i] + sin(T*2*M_PI/n);
		T++;
		dfs(j,i);
	}
}

int main() {
	cin >> n;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(0);
	cout << fixed << setprecision(8);
	for (int i = 0; i < n; i++) cout << x[i] << " " << y[i] << endl;
}
