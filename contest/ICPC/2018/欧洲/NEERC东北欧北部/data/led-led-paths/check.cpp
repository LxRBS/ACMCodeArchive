#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const string COLORS = "RGB";
const int C = COLORS.length();
const int DESIRED = 42;

vector<int> color;
vector<map<int, int> > edges;
vector<bool> mark;
vector<vector<int> > a;

void dfs(int v) {
	a[v].resize(C);
	mark[v] = true;
	for (map<int, int>::iterator it = edges[v].begin(); it != edges[v].end(); ++it) {
		int u = it->first;
		int c = color[it->second];
		//int c = color[edges[v][u]];
		if (!mark[u]) {
			dfs(u);
		}
		a[v][c] = max(a[v][c], a[u][c] + 1);
	}
}

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);

	int n = inf.readInt();
	int m = inf.readInt();
	edges.resize(n);
	for(int i = 0; i < m; i++) {
		int u = inf.readInt() - 1;
		int v = inf.readInt() - 1;
		color.push_back(COLORS.find(ouf.readToken("[" + COLORS + "]")));
		edges[u][v] = i;
	}
	mark.resize(n);
	a.resize(n);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (!mark[i]) {
			dfs(i);
		}
		ans = max(ans, *max_element(a[i].begin(), a[i].end()));
	}
	if (ans > DESIRED) {
		quitf(_wa, "Single color path of length %d", ans);
	}
	quitf(_ok, "All single color paths have length <= %d", ans);
}
