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
void reachable(ll t){
	priority_queue<pair<ll,int> > q;
	q.push(make_pair(0,n-1));
	dst[n-1] = 0;
	FOR(i,0,n-1) dst[i] = oo;

	while (sz(q)){
		pair<ll,int> i = q.top(); q.pop();
		if (dst[i.second] != -i.first) continue;
		
		FOR(j,0,sz(bdj[i.second])){
			ll ndst = i.first - wbdj[i.second][j];
			if (-ndst > t) continue;
			//cout << ndst << " -> " << bdj[i.second][j] << endl;
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


	ll lo = -1;
	ll hi = 1000000000000LL;
	while (abs(hi-lo) > 1){
		ll mi = (hi+lo) / 2;
		//mi = 1;
		bool fail = false;

		reachable(mi); // starting from A, we have to be in the reachable set
		// determine which edges in reachable are ok
		FOR(i,0,n) FOR(j,0,sz(adj[i])) eok[i][j] = dst[adj[i][j]] != oo && wadj[i][j] + dst[adj[i][j]] <= mi;
		
		forward(A); // check where we can R go to up to time A
		

		//FOR(i,0,n) cout << i << " " << dst[i] << " " << fdst[i]  << endl;
		
		// where can R be at time A
		set<int> start;
		FOR(i,0,n) if (dst[i] != oo && fdst[i] != oo) start.insert(i); 
		map<int,ll> edges;
		FOR(i,0,n) if (dst[i] == oo && fdst[i] != oo) FOR(e,0,sz(adj[i]))
			if (dst[adj[i][e]] != oo && fdst[adj[i][e]] == oo){
				//cout << "TEST" << i << "-" << adj[i][e] << endl;
				if (wadj[i][e] - (mi - dst[adj[i][e]]) + fdst[i] <= A)
					edges[adj[i][e]] = mi - dst[adj[i][e]], start.insert(adj[i][e]);
			}

		if (!sz(start) && !sz(edges)) fail = true;
	
		//cout << endl << "START" << endl;
		//FORIT(i,start) cout << "vertex " << *i << endl;
		//FORIT(i,edges) cout << "edge " << i->first << " l = " << i->second  << endl;

		// can R stay in dst != oo until B or for eternity
		FOR(i,0,n) lpath[i] = 0, visi[i] = 0;
		topC = 0;
		bool cycleFound = false;
		FORIT(i,start) {
			lpath[*i] = max(lpath[*i], edges[*i]);
			if (visi[*i]) continue;
			cycleFound |= dfs(*i);
		}
	
		//cout << "CYCLE " << cycleFound << endl;
		
		if (!cycleFound && dst[0] != oo)
			cycleFound = dst[0] <= mi; // if we can wait at 0, wait for the call and then drive

		// if we have not found a cycle, compute longest path	
		if (!cycleFound){
			FORD(t,0,topC){
				int i = backord[t];
				FOR(j,0,sz(adj[i])) if (eok[i][j]) lpath[adj[i][j]] = max(lpath[adj[i][j]], lpath[i] + wadj[i][j]);
			}
			//cout << "LPATH " << lpath[n-1] << endl;
			if (lpath[n-1] >= B-A) cycleFound = true;
		}

		//cout << "Result: " << fail << " " << cycleFound << endl;
		if (!fail && cycleFound) hi = mi; else lo = mi;
	}


	cout << hi << endl;
	

}
