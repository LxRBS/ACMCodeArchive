#include <bits/stdc++.h>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


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

#define MAXN 1000010

int cost[MAXN];
int pre[MAXN];
int nPre[MAXN],nPost[MAXN];
vi adj[MAXN];

//V log V log W + E
int main(){
	int n; cin >> n;
	int hi = 0;
	FOR(i,0,n){
		cin >> cost[i];
		hi = max(hi,cost[i]);

		cin >> nPost[i];
		FOR(j,0,nPost[i]){
			int t; cin >> t; --t;
			adj[i].push_back(t);
      nPre[t]++;
		}
	}


	// binary search the answer
	int lo = 0; hi += n;
  //log W
	while (lo + 1 < hi){
		int mi = (hi + lo) / 2;
		// greedy try to solve
		set<pii> first;

		FOR(i,0,n){
			pre[i] = 0;
			if (!nPre[i]) first.insert(make_pair(cost[i],i));
		}

		bool ok = true;
    //V
		FOR(i,0,n){
      //log V
			auto biggest = first.lower_bound(make_pair(mi-n+i+1,oo));
			if (biggest == first.begin()){
				ok = false;
				break;
			}
			biggest--; // take the largest one we can fit into
			int j = biggest->second;
      //O(1) amortized
			first.erase(biggest);

      //O(1) amortized iterations
			FORIT(k,adj[j]){
				pre[*k]++;
				if (pre[*k] == nPre[*k]){
          //log V
					first.insert(make_pair(cost[*k],*k));
				}
			}
		}

		if (ok) hi = mi; else lo = mi;
	}

	cout << hi << endl;
}
