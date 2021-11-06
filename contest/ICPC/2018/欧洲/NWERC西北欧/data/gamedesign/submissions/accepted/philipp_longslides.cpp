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
	set<pii> walls;
	FOR(i,0,moves.size()) {
		FOR(j,0,pow(2, i+1)) {
			pii ne = cur;
			ne.xx += moves[i].xx, ne.yy += moves[i].yy;
			if(walls.count(ne)) {
				break;
			}
			path.emplace(cur = ne);
		}
		pii wall = cur;
		wall.xx += moves[i].xx, wall.yy += moves[i].yy;
		walls.insert(wall);
	}
	pii goal = cur;

	cur = {0,0};
	FOR(i,0,moves.size()) {
		bool okay = false;
		while(true) {
			pii ne = cur;
			ne.xx += moves[i].xx, ne.yy += moves[i].yy;
			if(cur == goal && i != moves.size()-1) {
				okay = false;
				break;
			}
			if(walls.count(ne)) {
				break;
			}
			if(max(abs(ne.xx), abs(ne.yy)) > 2'000'000) {
				okay = false;
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
	if(cur != goal) {
		cout << "iMPOSSiBLE" << endl;
		return 0;
	}

	cout << -goal.xx << ' ' << -goal.yy << endl;
	cout << walls.size() << endl;
	for(pii p : walls) {
		cout << p.xx - goal.xx << ' ' << p.yy - goal.yy << endl;
	}
}
