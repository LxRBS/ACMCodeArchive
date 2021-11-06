#include <bits/stdc++.h>
using namespace std;

bool is_zigzag(string s) {
	return s == "LRL" || s == "RLR" || s == "UDU" || s == "DUD";
}

int main() {
	string s; cin >> s;

	if (s.size() >= 3 && is_zigzag(s.substr(s.size()-3))) {
		cout << "impossible" << endl;
		return 0;
	}
	
	int x = 0, y = 0, step = 3;
	set<pair<int,int>> res;

	for (int i = 0; i < int(s.size()); i++) {
		int dx = (s[i] == 'R') - (s[i] == 'L');
		int dy = (s[i] == 'U') - (s[i] == 'D');
		
		if (i >= 2 && is_zigzag(s.substr(i-2,3))) step -= 3;

		x += step*dx, y += step*dy;
		res.emplace(x+dx, y+dy);
		
		step += 3;
	}
	
	cout << -x << " " << -y << endl;
	cout << res.size() << endl;
	for (auto p: res) cout << p.first-x << " " << p.second-y << endl;
}
