#include <iostream>
#include <set>

using namespace std;

#define MAXN 14

long long dst[MAXN][MAXN];

// Set containing (used, total distance) pairs for routes
// from 0 to the current midpoint of the route
set<pair<int,long long> > can;

bool possible;
int midpoint, N;

// recursively try routes of length N/2
// i = current node
// used = bitmask of used nodes
// t = number of nodes used
// d = total distance so far
void rec1(int i, int used, int t, long long d) {
	if(t == 0) {
		if(i != midpoint) return;
		can.insert(pair<int,long long>(used, d));
	} else if(t == 1) {
		rec1(midpoint, used|(1<<i), t-1, d+dst[i][midpoint]);
	} else {
		for(int j = 0; j < N; j++) {
			if(i == j || j == midpoint || (used & (1<<j)) > 0) continue;
			rec1(j, used|(1<<i), t-1, d+dst[i][j]);
		}
	}
}

void rec2(int i, int used, int t, long long d) {
	if(t == 0) {
		if(i != midpoint) return;
		possible |= can.find(pair<int,long long>(used ^ ((1<<N)-1) ^ (1<<midpoint) ^ 1,d)) != can.end();
	} else if(t == 1) {
		rec2(midpoint, used|(1<<i), t-1, d-dst[i][midpoint]);
	} else {
		for(int j = 0; j < N; j++) {
			if(i == j || j == midpoint || (used & (1<<j)) > 0) continue;
			rec2(j, used|(1<<i), t-1, d-dst[i][j]);
		}
	}
}

int main() {
	// Read input
	long long L;
	cin >> N >> L;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			cin >> dst[i][j];

	// Meet-in-the-middle approach, loop over midpoint
	// and try to combine two routes from 0 -> midpoint
	// via a distinct set of nodes
	possible = false;
	for(midpoint = 1; midpoint < N; midpoint++) {
		can.clear();
		int u1 = N / 2;
		rec1(0, 0, u1, 0);
		rec2(0, 0, N - u1, L);
	}
	
	cout << (possible ? "possible" : "impossible") << endl;
	
	return 0;
}
