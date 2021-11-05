
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
ll x[MAXN]; // positions
ll N, P, R;
int main(int argc, char* argv[]) {
#if 0 // read from file
	if(argc == 3){
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
#endif
	cin >> N >> P >> R;
	FOR(i,0,N)cin >> x[i];
	sort(x,x+N);
	ll MINDIST = (1LL<<60);
	ll MAXDIST = 0;
	ll AVERAGE = 0;
	ll RUNS = 0;
	
	// try all possible starts
	ll laststart = x[(int)N-1] - P;
	FOR(j,0,N){
		if(x[j] != laststart){ // calculate values for current start if not already done
			// initialize available targets
			multiset<int> aims;
			// insert all possible targets
			FOR(i,0,N)aims.insert(x[i]);
			aims.erase(aims.find(x[j])); // initial target is destroyed
			ll DIST = R; // represents the time since this test run has started
			// DIST is initially R as it counts storing the initial bag
			ll cur = x[j]; // current position
			FOR(i,1,N){
				// calculate next possible position
				ll nco = cur + R;
				nco %= P;
				ll n;
				if(aims.lower_bound(nco) == aims.end())n = *(aims.begin());
				else n = *(aims.lower_bound(nco));
				// calculate the waiting time to shoot at the next target 
				ll dist = n - cur;
				ll toGo = R - dist;
				dist += ((toGo + P - 1) / P) * P; // do not forget the full cycles such recharging is finished
				// update distance and remove next object
				DIST += dist;
				cur = n;
				aims.erase(aims.find(cur));
			}
			// update result values
			ll mult = x[j] - laststart;
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
}
