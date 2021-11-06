// This only prints one box for each horizontal<>vertical change
#include <bits/stdc++.h>
using namespace std;
map<char, pair<int,int>> d{{'R', {1,0}}, {'L', {-1,0}}, {'D', {0,-1}}, {'U', {0, 1}}};
int main(){
	string s; cin >> s; reverse(s.begin(), s.end());
	int x = 0, y = 0, p = 10, ok = -3, streak = 0;
	char l = 'X';
	vector<pair<int,int>> ans;
	for(auto c : s){
		if(d[l].first*d[c].first+d[l].second*d[c].second != 0){
			++streak;
			if(++ok == 2) return cout << "impossible\n", 0;
			else continue;
		}
		streak = 1;
		if(ok >= 0) ans.push_back({x + d[c].first, y + d[c].second});
		x -= p*d[c].first, y -= p*d[c].second;
		//ans.push_back({x,y});
		x += 2*d[c].first, y += 2*d[c].second;
		p*=2, l=c, ok += 3;
	}
	cout << x << ' ' << y << '\n' << ans.size() << '\n';
	for(auto p : ans) cout << p.first << ' ' << p.second << endl;
}
