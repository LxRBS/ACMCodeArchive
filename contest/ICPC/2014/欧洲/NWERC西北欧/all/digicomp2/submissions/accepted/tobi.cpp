#include <iostream>
#include <algorithm>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
bool state[1000005];
long long M, indeg[1000005], balls[1000005], cur, ende, succ[1000005][2], q[1000005];
char initial;

int main() {
	cin >> balls[1] >> M;
	FOR(i, 1, M+1) {
		cin >> initial >> succ[i][0] >> succ[i][1];
		state[i] = initial == 'L';
		FOR(j, 0, 2) indeg[succ[i][j]]++;
	}
	FOR(i, 1, M+1) if (indeg[i] == 0) q[ende++] = i;
	while (q[cur] != 0) {
		int node = q[cur++];
		FOR(j, 0, 2) {
			balls[succ[node][j]] += (balls[node] + (state[node] == 1-j))/2;
			indeg[succ[node][j]]--;
			if (indeg[succ[node][j]] == 0 && q[ende-1] != succ[node][j]) q[ende++] = succ[node][j];
		}
		if (balls[node] % 2) state[node] = !state[node];
	}
	FOR(i, 1, M+1) cout << (state[i] ? 'L' : 'R');
	cout << endl;
	return 0;
}
