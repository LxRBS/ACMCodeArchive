#include <iostream>
#include <stack>
#include <cstring>

#define MAXM 1000001

using namespace std;

char state[MAXM];
int out1[MAXM];
int out2[MAXM];

int incoming[MAXM];
bool done[MAXM];
bool invisit[MAXM];

stack<int> order;

void topsort(int i) {
	if(invisit[i]) { cerr << "Not DAG" << endl; exit(1); }
	if(done[i]) return;
	invisit[i] = true;
	topsort(out1[i]);
	topsort(out2[i]);
	invisit[i] = false;
	done[i] = true;
	order.push(i);
}

int main() {
	int N, M;
	cin >> N >> M;
	for(int i = 1; i <= M; i++)
		cin >> state[i] >> out1[i] >> out2[i];

	// Topsort
	memset(done, false, sizeof(done));
	memset(invisit, false, sizeof(invisit));
	done[0] = true;
	for(int i = 1; i <= M; i++)
		if(!done[i])
			topsort(i);

	// Simulate
	memset(incoming, 0, sizeof(incoming));
	incoming[1] = N;
	while(order.size() > 0) {
		int cur = order.top(); order.pop();

		if (state[cur] == 'L') {
			incoming[out1[cur]] += (incoming[cur] + 1) / 2;
			incoming[out2[cur]] += incoming[cur] / 2;
			if (incoming[cur] & 1) state[cur] = 'R';
		} else {
			incoming[out1[cur]] += incoming[cur] / 2;
			incoming[out2[cur]] += (incoming[cur] + 1) / 2;
			if (incoming[cur] & 1) state[cur] = 'L';
		}
	}

	for(int i = 1; i <= M; i++)
		cout << state[i];
	cout << endl;

	return 0;
}
