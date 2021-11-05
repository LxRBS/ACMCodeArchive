
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

vi x, y;
int percentage;

// isOnLine returns true if the i-th point lies on the line represented by the index pair in "line"
bool isOnLine(int i, pii line){
	int f = line.first, t = line.second;
	ll dx = y[t] - y[f];
	ll dy = x[f] - x[t];
	return dx * x[f] + dy * y[f] == dx * x[i] + dy * y[i];
}

// muchPointsOnLine returns true if on the line represented by the index pair "line"
// contains at least M points in the index range f to t
bool muchPointsOnLine(pii line , int f, int t, int M){
	FOR(i,f,t)if(isOnLine(i,line))--M;
	return M <= 0;
}

// sameLine returns true if the index pairs represent the same line
bool sameLine(pii line1, pii line2){
	return isOnLine(line1.first, line2) && isOnLine(line1.second, line2);
}


// find(f,t) returns all lines, which contains at least floor((t - f) / 2) points
// from the index range f to t
vector<pii> find(int f, int t){
	if(((t - f) / 2) * percentage  <= 2 * 200){ // if number of points is small all index pairs need to be analysed
		vector<pii> res;
		FOR(i,f,t)FOR(j,f,i){
			if(muchPointsOnLine(mp(j,i), f, t, (percentage * (t-f))/100)){
				res.pb(mp(j,i));
			}
		}
		return res;
	}
	// else try all possible lines of the first and second half
	vector<pii > res, a, b;
	int mid = f + (t-f) / 2;
	a = find(f,mid);
	b = find(mid,t);
	FOR(i,0,sz(a))FOR(j,0,sz(b)){
		if(sameLine(a[i], b[j])){
			res.pb(a[i]);
			swap(a[i], a[sz(a)-1]);
			a.pop_back();
			swap(b[j], b[sz(b)-1]);
			b.pop_back();
			--i;
			j = oo;
		}
	}
	FORIT(it,b)a.pb(*it);
	FORIT(it,a){
		if(muchPointsOnLine(*it, f, t, (percentage *(t-f))/100)){
			res.pb(*it);
		}
	}
	return res;
}

// returns true if a line with ceil(N/2) points on it exists
bool findLine(){
	if(sz(x) * percentage <= 2 * 100)return true;
	vector<pii> lines = find(0, sz(x));
	FORIT(it, lines){
		if(muchPointsOnLine(*it, 0, sz(x), (sz(x) * percentage + 99) / 100)){
			return true;
		}
	}
	return false;
}


int main(int argc, char* argv[]) {
#if 0 // read from file
	if(argc == 3){
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
#endif
	int N;
	cin >> N;
	cin >> percentage;
	x = vi(N);
	y = vi(N);
	FOR(i,0,N)cin >> x[i] >> y[i];
	if(findLine())cout << "possible\n";
	else cout << "impossible\n";
	return 0;
}
