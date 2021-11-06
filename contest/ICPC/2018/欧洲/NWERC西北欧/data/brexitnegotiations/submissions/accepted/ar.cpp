// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;
// TODO no cyclic dependencies??
const int MAXN = 1.1e6;
vector<int> adj[MAXN];
int needed[MAXN], indegree[MAXN];
int main(){
    int N,M,tmp;
    cin >> N;
    for(int i = 0; i < N; i++){
        adj[i].clear();
    }
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    for(int i = 0; i < N; i++){
        cin >> needed[i] >> M;
        while(M-->0){
            cin >> tmp; --tmp;
            adj[i].push_back(tmp);
            indegree[tmp]++;
        }
    }
    for(int i = 0; i < N; i++){
      if (indegree[i] == 0){
        q.emplace(needed[i],i);
      }
    }
    int res = 0;
    while(!q.empty()){
        auto it = q.top();
        q.pop();
        int n = it.second;
        res = max(res + 1, needed[n]);
        for(auto to: adj[n]){
            if(--indegree[to] == 0){
                q.push(make_pair(needed[to],to));
            }
        }
    }
    cout << res << endl;
	return 0;
}
