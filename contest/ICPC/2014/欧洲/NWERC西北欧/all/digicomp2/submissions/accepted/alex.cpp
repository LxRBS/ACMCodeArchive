// author: Alexander Rass
#include <queue>
#include <iostream>

using namespace std;

typedef long long ll;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

const int MAXM = 1000100;
int M;
ll N;

ll todo[MAXM];
int indeg[MAXM];
int adj[MAXM][2];
string LR;
int main() {
	cin >> N >> M;
	FOR(i,0,M+1)todo[i] = 0;
	todo[1] = N;
	FOR(i,0,M+1)indeg[i] = 0;
	LR = string(M+1, ' ');
	FOR(i,1,M+1){
		string tmp;
		cin >> tmp >> adj[i][0] >> adj[i][1];
		LR[i] = tmp[0];
	}
	FOR(i,1,M+1)FOR(j,0,2)indeg[adj[i][j]]++;
	queue<int> q;
	FOR(i,1,M+1)if(indeg[i] == 0)q.push(i);
	while(!q.empty()){
		int m = q.front();
		q.pop();
		ll td = todo[m] / 2;
		FOR(i,0,2){
			todo[adj[m][i]] += td;
			if(0 == --indeg[adj[m][i]]){
				q.push(adj[m][i]);
			}
		}
		if(todo[m]&1){
			if(LR[m] == 'L'){
				LR[m] = 'R';
				++todo[adj[m][0]];
			} else {
				LR[m] = 'L';
				++todo[adj[m][1]];
			}
		}
	}
	cout << LR.substr(1) << endl;
	return 0;
}
