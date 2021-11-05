// solution by Alexander Rass
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)


int main() {
	int N,tmp1, tmp2;
	scanf("%d",&N);
	vector<int> ct(N+1);
	vector<vector<int> > adj(N+1);
	int F = 1;
	FOR(i,1,N){
		scanf("%d %d", &tmp1, &tmp2);
		adj[tmp1].push_back(tmp2);
		adj[tmp2].push_back(tmp1);
	}
	queue<int> q;
	FOR(i,1,N+1)if(1 == adj[i].size()){
		q.push(i);
		break;
	}
	vector<vector<int> > freq(N+1, vector<int>(2,1));
	vector<bool> done(N+1, false);
	while(!q.empty()){
		int n = q.front();
		done[n] = true;
		freq[n][1] = F++;
		q.pop();
		FOR(i,0,(int)(adj[n].size())){
			int t = adj[n][i];
			if(done[t])continue;
			q.push(t);
			freq[t][0] = freq[n][1];
		}
	}
	if(N==2)freq[1][0] = 2;
	FOR(i,1,N+1)printf("%d %d\n", freq[i][0], freq[i][1]);
	return 0;
}
