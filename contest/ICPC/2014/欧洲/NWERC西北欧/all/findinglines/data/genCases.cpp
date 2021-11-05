

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

void usage(){
	cout << "./genCases\n"
	 << "initializes generation\n"
	 << "possible inputs are:\n"
	 << "<seed> line <N> <p> <numLines> <number of points on first line> <number of points on second line> ... <number of points on last line> <variance of points on the line>\n"
	 << "produces input with specified parameters N and p and generates point as given with the line specification. Remaining points are placed randomly.\n\n"
	 << "<seed> rand large <N> <p>\n"
	 << "produces input with specified parameters N and p - places all points randomly in the whole possible range (0 to 1000000000)\n\n"
	 << "<seed> rand small <N> <p>\n"
	 << "produces input with specified parameters N and p - places all points randomly in the range 0 to 100\n";
}

const int MAXVAL = 1000000000;
set<pii> used;
bool canInsert(pii pos){
	if(used.find(pos) != used.end())return false;
	used.insert(pos);
	return true;
}
void getDelta(int &dx, int &sx, int &fx, int &tx, int len, int VAR){
	sx = rand() % (MAXVAL + 1);
	dx = 0;
	while(dx == 0)dx = rand() % (MAXVAL / (len * VAR));
	fx = sx / dx;
	tx = (MAXVAL - sx) / dx;
	if(rand()&1){
		dx = -dx;
		swap(fx, tx);
		fx = -fx;
		tx = -tx;
	}
}

int main(){
	ll seed;
	cin >> seed;
	srand(seed);
	string in;
	cin >> in;
	if(in == "rand"){
		cin >> in;
		int MOD = MAXVAL + 1;
		if(in == "small"){
			MOD = 101;
		}
		int N, p;
		cin >> N >> p;
		cout << N << endl << p << endl;
		FOR(i,0,N){
			int a = (rand() % MOD);
			int b = (rand() % MOD);
			if(used.find(mp(a,b)) != used.end()){
				--i;
				continue;
			}
			used.insert(mp(a,b));
			cout << a << " " << b << endl;
		}
	} else if(in == "line"){
		int N, p;
		cin >> N >> p;
		vi lineLens;
		int L;
		int VAR;
		cin >> L;
		while(L--){
			int len;
			cin >> len;
			lineLens.pb(len);
		}
		cin >> VAR;
		FOR(ii,0,sz(lineLens)){
			int len = lineLens[ii];
			int dx, sx, fx, tx;
			int dy, sy, fy, ty;
			int maxi, mini;
			while(true){
				getDelta(dx, sx, fx, tx, len, VAR);
				getDelta(dy, sy, fy, ty, len, VAR);
				maxi = min(tx, ty);
				mini = max(fx, fy);
				if(maxi - mini < len * VAR / 3)continue;
				break;
			}
			int MOD = maxi - mini + 1;
			while(len > 0){
				int ran = rand() % MOD;
				int x = dx * (ll)(ran + mini) + sx;
				int y = dy * (ll)(ran + mini) + sy;
				if(canInsert(mp(x,y)))--len;
			}
		}
		while(sz(used) < N){
			int x = rand() % (MAXVAL+1);
			int y = rand() % (MAXVAL+1);
			canInsert(mp(x,y));
		}
		vector<pii> pts(all(used));
		random_shuffle(all(pts));
		assert(sz(pts) == N);
		cout << N << endl << p << endl;
		FOR(i,0,N)cout << pts[i].first << " " << pts[i].second << endl;
	} else if(in == "special1"){ // possible float errors
		int caseid;
		cin >> caseid;
		int N = 100000;
		cout << N << endl << 20 << endl;
		int hv = caseid & 1;
		int possible = (caseid >> 1) & 1;
		vector<pii > pts;
		FOR(d,0,5){
			FOR(t,0,20000){
				pts.push_back(make_pair(MAXVAL-1*t, 50002*t+d));
			}
			if(d != 2 || possible != 1){
				pts[d*20000+12345]=make_pair(rand()%MAXVAL, rand() % MAXVAL);
			}
		}
		if(hv)FOR(i,0,N)swap(pts[i].first,pts[i].second);
		random_shuffle(pts.begin(), pts.end());
		FOR(i,0,N)cout << pts[i].first << " " << pts[i].second << endl;
	} else if(in == "special2"){ // possible errors if points on line are as far away as possible
		int N = 1<<16;
		cout << N << endl << 20 << endl;
		FOR(i,0,N){
			if(i%5==0){
				cout << i * 37 << " " << MAXVAL - i * 43 << endl;
			} else {
				cout << rand() % MAXVAL << " " << rand() % MAXVAL << endl;
			}
		}
		// line is at front // middle // end
	} else if(in == "specialfront"){
		cout << 100000 << "\n" << 23 << endl;
		FOR(i,0,23000){
			cout << MAXVAL - 34521 - i * 23 << " " << 34521+i*51 << endl;
		}
		FOR(i,0,77000){
			cout << rand() % MAXVAL << " " << rand() % MAXVAL << endl;
		}
	} else if(in == "specialmid"){
		cout << 100000 << "\n" << 22 << endl;
		FOR(i,0,39000){
			cout << rand() % MAXVAL << " " << rand() % MAXVAL << endl;
		}
		FOR(i,0,22000){
			cout << MAXVAL - 34521 - i * 23 << " " << 34521+i*51 << endl;
		}
		FOR(i,0,39000){
			cout << rand() % MAXVAL << " " << rand() % MAXVAL << endl;
		}
	} else if(in == "specialend"){
		cout << 100000 << "\n" << 24 << endl;
		FOR(i,0,76000){
			cout << rand() % MAXVAL << " " << rand() % MAXVAL << endl;
		}
		FOR(i,0,24000){
			cout << MAXVAL - 34521 - i * 23 << " " << 34521+i*51 << endl;
		}
	} else {
		usage();
	}
	return 0;
}
