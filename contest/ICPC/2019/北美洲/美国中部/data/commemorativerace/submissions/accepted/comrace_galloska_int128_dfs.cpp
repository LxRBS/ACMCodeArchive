#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli __int128 
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const int MAXN = 100001;

struct ura {
	int path;
	lli ways;

	ura() {}
	ura(int a, lli b): path(a), ways(b) {}
	bool operator == (const ura& cmp) const { return path == cmp.path && ways == cmp.ways; }
	ura operator + (const int& k) const { return ura(path + k, ways); };
};

ura maxi(const ura& a, const ura& b) {
	if(a.path > b.path) return a;
	if(b.path > a.path) return b;
	return ura(a.path, a.ways + b.ways);
}

vi order;
ura dp[MAXN];
ura dpRev[MAXN];
bool vis[MAXN];
vi adj[MAXN];
vi adjRev[MAXN];

vector<pii> paths[MAXN];
vector<pii> pathsRev[MAXN];

void dfs(int u) {
	vis[u] = 1;
	for(auto &v: adj[u])
		if(!vis[v])
			dfs(v);
	order.pb(u);
}

void topologicalSort(int n) {
	forn(i, n)
		if(!vis[i])
			dfs(i);
}

void computeDP(int a = -1, int b = -1) {
	for(auto &u: order) paths[u].clear();
	for(auto &u: order) {
		ura ans(0, 1);
		for(auto &v: adj[u]) {
			if(u == a && v == b) continue; // Ignore edge to be removed.
			ans = maxi(ans, dp[v] + 1);
			paths[u].pb(pii((dp[v] + 1).path, v));
		}
		dp[u] = ans;
	}
}

void computeBackDP() {
	reverse(order.begin(), order.end());
	for(auto &u: order) pathsRev[u].clear();
	for(auto &u: order) {
		ura ans(0, 1);
		for(auto &v: adjRev[u]) {
			ans = maxi(ans, dpRev[v] + 1);
			pathsRev[u].pb(pii((dpRev[v] + 1).path, v));
		}
		dpRev[u] = ans;
	}
	reverse(order.begin(), order.end());
}

ura findLongestPath(int n) {
	ura best(0, 0);
	forn(u, n) 
		if(!adjRev[u].size()) 
			best = maxi(best, dp[u]);
	return best;
}

vector<pii> findLongestPathEdges(int n) {
	vector<pii> edges;
	ura best = findLongestPath(n);
	forn(u, n)
		for(auto &v: adj[u]) {
			ura cur(dp[v].path + dpRev[u].path + 1, dpRev[u].ways * dp[v].ways);
			if(cur == best) edges.pb(pii(u, v));
		}
	return edges;
}

int maxDistanceInEdge(int u, int v) {
	int one = 0;
	// Find longest path passing through node u.
	for(auto &it: paths[u])
		if(it.se != v) {
			one += it.fi;
			break;
		}
	for(auto &it: pathsRev[u])
		if(it.se != v) {
			one += it.fi;
			break;
		}
	return one;
}

// чтение и перевод это будет пустой тратой времени
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m,u,v;
	cin>>n>>m;
	forn(i, m) {
		cin>>u>>v;
		u--,v--;
		adj[u].pb(v);
		adjRev[v].pb(u);
	}

	topologicalSort(n);
	computeDP();
	computeBackDP();
	vector<pii> edges = findLongestPathEdges(n);

	if(!edges.size()) {
		ura answer = findLongestPath(n);
		cout<<answer.path<<endl;
		return 0;
	}

	// Sort distances by decresing order.
	forn(u, n) {
		sort(paths[u].begin(), paths[u].end());
		reverse(paths[u].begin(), paths[u].end());
		sort(pathsRev[u].begin(), pathsRev[u].end());
		reverse(pathsRev[u].begin(), pathsRev[u].end());
	}

	int mini = 1e9, id = 0;
	forn(i, edges.size()) {
		u = edges[i].fi, v = edges[i].se;
		int d = maxDistanceInEdge(u, v);
		if(d < mini) {
			mini = d;
			id = i;
		}
	}
	cout<<mini<<endl;
	return 0;
}
