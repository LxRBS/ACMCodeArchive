#include <bits/stdc++.h>

using namespace std;

void check_each_road_exitable(vector<vector<uint32_t>>& adj){
	// for each intersection, there is a way to another intersection.
	for(uint32_t i = 1; i < adj.size(); i++){
		if(!adj[i].size()){
			cerr << "Intersection " << i << " not exitable" << endl;
			exit(43);
		}
	}
}

void check_reachable(vector<vector<uint32_t>>& adj){

	vector<bool> inqueue(adj.size());
	stack<uint32_t> q;

	//Richards house is at position 1
	q.push(1);
	inqueue[1] = true;

	while(!q.empty()){
		uint32_t cur = q.top();
		q.pop();

		//Reached destination aka Janets house
		if(cur + 1 == adj.size()){
			return;
		}

		for(auto& neigh : adj[cur]){
			if(!inqueue[neigh]){
				q.push(neigh);
				inqueue[neigh] = true;
			}
		}
	}

	cerr << "Destination not reachable from start!" << endl;
	exit(43);
}

int main(){

	// read A and B, unnecessary here.
	uint64_t A, B;
	cin >> A >> B;

	// road intersections and roads in neighborhood
	uint64_t n, m;
	cin >> n >> m;

	vector<vector<uint32_t>> adj(n+1);

	for(uint32_t i = 0; i < m; i++){
		// from u to v in t minutes (t is ignored)
		uint32_t u, v, t;
		cin >> u >> v >> t;

		adj[u].push_back(v);
	}

	check_each_road_exitable(adj);
	check_reachable(adj);

	exit(42);
}
