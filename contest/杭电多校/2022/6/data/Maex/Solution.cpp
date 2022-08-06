#include <bits/stdc++.h>
using namespace std;
const int N = 500000 + 10;
vector<int> g[N];
int siz[N];
long long dp[N];
void dfs(int u, int fr){
    siz[u] = 1;
    dp[u] = 0;
	for(auto v : g[u]){
        if(v == fr) continue;
        dfs(v, u);
        siz[u] += siz[v];
        dp[u] = max(dp[u], dp[v]);
    }
    dp[u] += siz[u];
}
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
	while(T--){
	    int n; cin >> n;
	    for(int i = 0; i < n; i++) g[i].clear();
	    for(int i = 1; i < n; i++){
	        int u, v; cin >> u >> v;
	        --u; --v;
	        g[u].emplace_back(v);
	        g[v].emplace_back(u);
	    }
	    dfs(0, -1);
	    cout << dp[0] << "\n";
	}
    return 0;
}
