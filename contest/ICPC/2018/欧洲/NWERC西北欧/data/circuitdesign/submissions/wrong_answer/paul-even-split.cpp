#include <bits/stdc++.h>
using namespace std;

// This solution recursively places the subtree rooted at
// some node i in the sector bounded by angles amin and
// amax. The sector is split into even parts for the child
// nodes.
//
// This approach is incorrect, because it causes ranges to
// become very small, which leads to collisions.

const int N = 1000;
vector<int> adj[N];
double x[N], y[N];

void dfs(int i, double amin, double amax, int p = -1) {
	int deg = adj[i].size() - (p != -1);
	if (deg == 0) return;
	
	int k = 0;
	for (int j: adj[i]) {
		if (j == p) continue;
		
		double bmin = amin +  k   *(amax-amin)/deg;
		double bmax = amin + (k+1)*(amax-amin)/deg;
		
		double b = (bmin+bmax)/2;
		x[j] = x[i] + cos(b);
		y[j] = y[i] + sin(b);
		
		dfs(j,bmin,bmax,i);
		k++;
	}
}

int main() {
	int n; cin >> n;
	
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(0,0,M_PI/2);
	cout << fixed << setprecision(8);
	for (int i = 0; i < n; i++) cout << x[i] << " " << y[i] << endl;
}
