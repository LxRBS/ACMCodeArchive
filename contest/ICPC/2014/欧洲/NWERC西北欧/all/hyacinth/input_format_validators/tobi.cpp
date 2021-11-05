#include <iostream>
#include <vector>
#include <map>
#include <deque>

using namespace std;
int N, from, to;
vector<int> adj[10005];
bool visited[10005];
#define MIN_N 2
#define MAX_N 10000

void visit(int n) {
	if (visited[n]) return;
	visited[n] = true;
	for (auto i : adj[n]) visit(i);
}

int main() {
	if (!(cin >> N)) {
		cerr << "could not parse N" << endl;
		return -1;
	}
	if (N < MIN_N || MAX_N < N) {
		cerr << "N = " << N << " out of bounds" << endl;
		return -1;
	}
	for (int i = 0; i < N - 1; i++) {
		if (!(cin >> from)) {
			cerr << "cannot parse edge" << endl;
			return -1;
		}
		if (!(cin >> to)) {
			cerr << "cannot parse edge" << endl;
			return -1;
		}
		if (from < 1 || N < from) {
			cerr << "from = " << from << " out of bounds" << endl;
			return -1;
		}
		if (to < 1 || N < to) {
			cerr << "to = " << to << " out of bounds" << endl;
			return -1;
		}
		from--, to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}
	visit(0);

	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			cerr << "node " << i << " not visited during dfs, input is not a tree" << endl;
			return -1;
		}
	}

	// input ok
	return 42;
}
