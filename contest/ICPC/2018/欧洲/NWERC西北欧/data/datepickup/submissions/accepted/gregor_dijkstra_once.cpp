#include <bits/stdc++.h>

using namespace std;

const long long oo = 0x3f3f3f3f3f3f3f3fLL;


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

#define MAXN 1000000

int n,m;

vi adj[MAXN];
vi bdj[MAXN];
vector<bool> eok[MAXN];

vi wadj[MAXN];
vi wbdj[MAXN];


ll dst[MAXN];
void reachable(){
	priority_queue<pair<ll,int> > q;
	q.push(make_pair(0,n-1));
	dst[n-1] = 0;
	FOR(i,0,n-1) dst[i] = oo;

	while (sz(q)){
		pair<ll,int> i = q.top(); q.pop();
		if (dst[i.second] != -i.first) continue;
		
		FOR(j,0,sz(bdj[i.second])){
			ll ndst = i.first - wbdj[i.second][j];
			if (-ndst > dst[bdj[i.second][j]]) continue;
			dst[bdj[i.second][j]] = -ndst;
			q.push(make_pair(ndst,bdj[i.second][j]));
		}
	}
}

ll fdst[MAXN];
void forward(ll A){
	priority_queue<pair<ll,int> > q;
	q.push(make_pair(0,0));
	fdst[0] = 0;
	FOR(i,1,n) fdst[i] = oo;

	while (sz(q)){
		pair<ll,int> i = q.top(); q.pop();
		if (fdst[i.second] != -i.first) continue;
		
		FOR(j,0,sz(adj[i.second])){
			ll ndst = i.first - wadj[i.second][j];
			if (-ndst > A) continue;
			if (-ndst > fdst[adj[i.second][j]]) continue;
			fdst[adj[i.second][j]] = -ndst;
			q.push(make_pair(ndst,adj[i.second][j]));
		}
	}
}


int visi[MAXN];
int backord[MAXN];
ll lpath[MAXN];
int topC;

bool dfs(int i){
	if (visi[i] == 1) return true; // found cycle
	if (visi[i] == 2) return false;
	visi[i] = 1;
	FOR(j,0,sz(adj[i]))	if (eok[i][j]) if (dfs(adj[i][j])) return true;
	visi[i] = 2;
	backord[topC++] = i; // add to inverse topological order;
	return false;
}


int main(){
	ll A,B; cin >> A >> B;
	cin >> n >> m;
	FOR(i,0,m){
		int u,v,t; cin >> u >> v >> t;
		u--,v--;

		adj[u].push_back(v);
		eok[u].push_back(false);
		wadj[u].push_back(t);

		bdj[v].push_back(u);
		wbdj[v].push_back(t);
	}

	forward(A); // check where we can R go to up to time A
	reachable();

	ll lo = -1;
	ll hi = 1000000000000LL;
	while (abs(hi-lo) > 1){
		ll mi = (hi+lo) / 2;
		bool fail = false;

		// determine which edges in reachable are ok
		FOR(i,0,n) FOR(j,0,sz(adj[i])) eok[i][j] = dst[adj[i][j]] <= mi && wadj[i][j] + dst[adj[i][j]] <= mi;

		// where can R be at time A
		vector<bool> start(n); bool any_start=false;
		FOR(i,0,n) if (dst[i] <= mi && fdst[i] != oo) start[i]=true, any_start=true;
		vector<ll> edges(n); bool any_edges=false;
		FOR(i,0,n) if (fdst[i] != oo) FOR(e,0,sz(adj[i])) if (dst[adj[i][e]] <= mi){
				if (wadj[i][e] - (mi - dst[adj[i][e]]) + fdst[i] <= A)
					edges[adj[i][e]] = mi - dst[adj[i][e]], start[adj[i][e]]=true, any_start=true, any_edges=true;
			}

		if (!any_start && !any_edges) fail = true;
	
		// can R stay in dst != oo until B or for eternity
		FOR(i,0,n) lpath[i] = 0, visi[i] = 0;
		topC = 0;
		bool cycleFound = false;
		FOR(i,0,n) if (start[i]){
			lpath[i] = max(lpath[i], edges[i]);
			if (visi[i]) continue;
			cycleFound |= dfs(i);
		}
	
		if (!cycleFound && dst[0] <= mi)
			cycleFound = dst[0] <= mi; // if we can wait at 0, wait for the call and then drive

		// if we have not found a cycle, compute longest path	
		if (!cycleFound){
			FORD(t,0,topC){
				int i = backord[t];
				FOR(j,0,sz(adj[i])) if (eok[i][j]) lpath[adj[i][j]] = max(lpath[adj[i][j]], lpath[i] + wadj[i][j]);
			}
			if (lpath[n-1] >= B-A) cycleFound = true;
		}
		if (!fail && cycleFound) hi = mi; else lo = mi;
	}
	cout << hi << endl;
}
