#include <iostream>
#include <vector>
#include <map>
#include <deque>

using namespace std;
int N, from, to, channel[10005][2];
bool adj[10005][10005];
map<int,bool> usedChannel;
bool visited[10005];
deque<int> nodeQ, freqQ;

int randChannel() {
	int c;
	do {
		c = rand() % 1000000000;
	} while (usedChannel[c]);
	usedChannel[c] = true;
	return c;
}

int main() {
	srand(time(NULL));
	cin >> N;
	if (N == 2) {
		channel[0][0] = randChannel();
		channel[0][1] = randChannel();
		cout << channel[0][0] << " " << channel[0][1] << endl;
		cout << channel[0][0] << " " << channel[0][1] << endl;
		return 0;
	}
	for (int i = 0; i < N - 1; i++) {
		cin >> from >> to;
		from--, to--;
		adj[from][to] = adj[to][from] = true;
	}
	for (int i = 0; i < N; i++) {
		int cnt = 0;
		for (int j = 0; j < N; j++) {
			if (adj[i][j]) cnt++;
		}
		if (cnt == 1) {
			nodeQ.push_back(i);
			break;
		}
	}
	freqQ.push_back(randChannel());
	while (nodeQ.size() > 0) {
		int node = nodeQ[0], freq = freqQ[0];
		nodeQ.pop_front(); freqQ.pop_front();
		if (visited[node]) continue;
		visited[node] = true;
		int which = rand() % 2;
		channel[node][which] = freq;
		channel[node][1-which] = randChannel();
		for (int i = 0; i < N; i++) if (adj[node][i] && !visited[i]) {
			freqQ.push_back(channel[node][1-which]);
			nodeQ.push_back(i);
		}
	}
	for (int i = 0; i < N; i++) {
		cout << channel[i][0] << " " << channel[i][1] << endl;
	}

	return 0;
}
