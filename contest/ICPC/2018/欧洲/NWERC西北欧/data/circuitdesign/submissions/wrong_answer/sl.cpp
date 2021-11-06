// Place nodes on positions (depth, counter for depth * 1e-9). Since the number
// of nodes at each depth is at most 1000, this results in distances between
// neighboring nodes which are not exactly 1, but close enough: they are at most
// sqrt(1 + (1000 * 1e-9) ^ 2) ~ 1 + 5e-13, safely within the 1e-6 error margin.
#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> ed[1000];
int pos[1000];
double x[1000], y[1000];

void rec(int at, int depth, int par) {
	y[at] = depth;
	x[at] = pos[depth]++ * 1e-9;
	for (int x : ed[at]) if (x != par)
		rec(x, depth+1, at);
}

int main() {
	cin >> N;
	assert(N <= 1000);
	for (int i = 0; i < N-1; i++) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		ed[a].push_back(b);
		ed[b].push_back(a);
	}
	rec(0, 0, -1);
	cout << setprecision(9) << fixed;
	for (int i = 0; i < N; i++) {
		cout << x[i] << ' ' << y[i] << endl;
	}
}
