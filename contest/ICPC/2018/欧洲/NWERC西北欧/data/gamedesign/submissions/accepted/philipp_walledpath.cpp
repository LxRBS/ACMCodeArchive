#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
#define xx first
#define yy second
#define FOR(i,a,b) for(int i = (a); i < (b); i++)

vector<pii> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int main() {
	cin.sync_with_stdio(0);

	string s;
	cin >> s;

	vector<pii> moves;
	FOR(i,0,s.size()) {
		pii dir;
		switch(s[i]) {
			case 'L':
				dir = dirs[0];
				break;
			case 'R':
				dir = dirs[1];
				break;
			case 'U':
				dir = dirs[2];
				break;
			case 'D':
				dir = dirs[3];
				break;
		}
		moves.push_back(dir);
	}

	set<pii> path;
	pii cur;
	path.emplace(cur = {0,0});
	map<pii, int> bounds;
	FOR(i,0,moves.size()) {
		int steps;
		FOR(j,0,2) {
			if(moves[i].xx) {
				bounds[moves[i]] += 2 * moves[i].xx;
				steps = moves[i].xx * (bounds[moves[i]] - cur.xx);
			}
			swap(moves[i].xx, moves[i].yy);
			swap(cur.xx, cur.yy);
		}
		FOR(j,0,steps) {
			cur.xx += moves[i].xx, cur.yy += moves[i].yy;
			path.emplace(cur);
		}
	}
	pii goal = cur;

	set<pii> walls;
	for(pii p : path) {
		FOR(i,0,4) {
			pii w = p;
			w.xx += dirs[i].xx, w.yy += dirs[i].yy;
			if(!path.count(w)) {
				walls.insert(w);
			}
		}
	}

	cur = {0,0};
	FOR(i,0,moves.size()) {
		bool okay = false;
		while(true) {
			pii ne = cur;
			ne.xx += moves[i].xx, ne.yy += moves[i].yy;
			if(cur == goal && (!walls.count(ne) || i != moves.size()-1)) {
				okay = false;
				break;
			}
			if(walls.count(ne)) {
				break;
			}
			okay = true;
			cur = ne;
		}
		if(!okay) {
			cout << "iMPOSSiBLE" << endl;
			return 0;
		}
	}

	cout << -goal.xx << ' ' << -goal.yy << endl;
	cout << walls.size() << endl;
	for(pii p : walls) {
		cout << p.xx - goal.xx << ' ' << p.yy - goal.yy << endl;
	}
}
