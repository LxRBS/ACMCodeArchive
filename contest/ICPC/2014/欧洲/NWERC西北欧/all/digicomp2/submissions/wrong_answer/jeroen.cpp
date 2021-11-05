#include <iostream>
#include <cstring>
#include <stack>

#define MAXM 1000001

using namespace std;

char state[MAXM];
int out1[MAXM];
int out2[MAXM];

int incoming[MAXM];
bool done[MAXM];

int main() {
	int N, M;
	cin >> N >> M;
	for(int i = 1; i <= M; i++)
		cin >> state[i] >> out1[i] >> out2[i];
	
	memset(incoming, 0, sizeof(incoming));
	memset(done, false, sizeof(done));
	done[0] = true;
	incoming[1] = N;
	stack<int> todo;
	todo.push(1);
	
	while(todo.size() > 0) {
		int cur = todo.top(); todo.pop();
		if(done[cur]) continue;
		done[cur] = true;

		todo.push(out1[cur]);
		todo.push(out2[cur]);

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
