
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <fstream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

// greatest common divisor
ll gcd(ll a, ll b){
	if(b)return gcd(b, a % b);
	return a;
}

const int MAXN = 1024*1024*10;
int x[MAXN]; // positions
int next_[MAXN]; // next possible index after shooting on the current index and recharging
int gNext[MAXN]; // next position to shoot at - for implementation of path compression
bool removed[MAXN]; // specifies whether this target is already eliminated

int FUNCCALLS = 0; // just counts number of getNext-function calls - for debugging

// getNext returns the id of the next target, which should be eliminated
// it uses path compression
int getNext(int n){
	++FUNCCALLS;
	if(removed[n]){
		return gNext[n] = getNext(gNext[n]);
	}
	return n;
}

int N, P, R;
int main(int argc, char* argv[]) {
	if(argc == 3){
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	cin >> N >> P >> R;
	FOR(i,0,N)cin >> x[i];
	sort(x,x+N);
	// calculate next possible position if recharging
	int toGo = (R) % P;
	bool fliped = false;
	FOR(i,0,N){
		next_[i] = (i>0?next_[i-1]:1);
		if(!fliped){
			while(next_[i] < N && x[next_[i]] < x[i] + toGo)++next_[i];
		}
		if(next_[i] == N){
			next_[i] = 0;
			fliped = true;
		}
		if(fliped) {
			while(x[next_[i]] + P < x[i] + toGo)++next_[i];
		}
	}
	ll MINDIST = (1LL<<60);
	ll MAXDIST = 0;
	ll AVERAGE = 0;
	ll RUNS = 0;
	
	// try all possible starts once
	int laststart = x[(int)N-1] - P;
	FOR(j,0,N){
		if(x[j] != laststart){ // calculate values for current start if not already done
			// initialize removed and gNext
			FOR(i,0,N)removed[i] = false;
			FOR(i,0,N)gNext[i] = (i+1);
			gNext[N-1] = 0;
			ll DIST = R; // represents the time since this test run has started
			// DIST is initially R as it counts storing the initial bag
			
			int cur = j; // current index
			removed[cur] = true; // initial target is destroyed
			FOR(i,1,N){
				int n = next_[cur]; // next possible index after recharging
				n = getNext(n); // next possible index which is not already removed
				// calculate the waiting time to shoot at the next target 
				int dist = x[n] - x[cur];
				toGo = R - dist;
				dist += ((toGo + P - 1) / P) * P; // do not forget the full cycles such recharging is finished
				// update distance and remove next object
				DIST += dist;
				cur = n;
				removed[n] = true;
			}
			// update result values
			int mult = x[j] - laststart;
			MINDIST = min(MINDIST, DIST);
			MAXDIST = max(MAXDIST, DIST + mult - 1);
			AVERAGE += DIST * mult;
			AVERAGE += (mult * (mult - 1)) / 2;
			RUNS += mult;
			laststart = x[j];
		}
	}
	ll gc = gcd(AVERAGE, RUNS);
	AVERAGE /= gc;
	RUNS /= gc;
	cout << MINDIST << endl << MAXDIST << endl << AVERAGE <<"/" << RUNS << endl;
	//cerr << FUNCCALLS << endl; // display recursive function calls for debugging
}
