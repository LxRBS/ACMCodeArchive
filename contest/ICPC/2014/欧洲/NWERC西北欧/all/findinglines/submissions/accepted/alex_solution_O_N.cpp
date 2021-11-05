
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

int gcd(int a, int b){
	if(b == 0)return a;
	return gcd(b, a % b);
}

// memoization of sampled gradients
int S = 0; // number of already sampled gradients
map<pii,int > gradients;
void insertGradient(int id1, int id2){
	// make gradient unique
	int dx = x[id1] - x[id2];
	int dy = y[id1] - y[id2];
	int g = gcd(abs(dx), abs(dy));
	dx /= g;
	dy /= g;
	if(dx < 0 || (dx == 0 && dy < 0)){
		dx *= -1;
		dy *= -1;
	}
	// memoization of gradient
	gradients[mp(dx,dy)] += 1;
	S++;
}

int main(int argc, char* argv[]) {
#if 0 // read from file:
	if(argc == 3){
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
#endif
	int N, p;
	cin >> N >> p;
	if(2 * 100 >= N * p){
		cout << "possible\n";
		return 0;
	}
	x = vi(N);
	y = vi(N);
	FOR(i,0,N)cin >> x[i] >> y[i];
	if(N * (ll)N < 10000){ // sample all gradients if N is small
		FOR(i,0,N)FOR(j,0,i)insertGradient(i,j);
	} else { // sample 10^4 gradients if N is large
		FOR(i,0,10000){
			int a = rand() % N;
			int b = rand() % N;
			while(b == a)b = rand() % N;
			insertGradient(a,b);
		}
	}
	vector<pair<int, pii > > grad;
	FORIT(it, gradients) grad.push_back(mp(it->second, it->first));
	sort(grad.begin(), grad.end(), greater<pair<int, pii > >());
	FOR(ii,0,sz(grad)){
		if(ii > 20)break; // do not too much iterations
		// it would be very inlikely that a line is not within the 20 most apearing slopes
		unordered_map<ll,int> t;
		// generate orthogonal vector to gradient
		ll dx = -(grad[ii].second.second);
		ll dy = grad[ii].second.first;
		// scalar product with orthogonal vector results in value which identifies
		// the position of the line
		FOR(i,0,N){
			ll scal = dx * x[i] + dy * y[i];
			t[scal] += 1;
		}
		FORIT(it, t){
			if(it->second * 100 >= N * p){
				cout << "possible\n";
				return 0;
			}
		}
	}
	cout << "impossible\n";
	return 0;
}
