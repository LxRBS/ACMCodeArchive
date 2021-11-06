#include <bits/stdc++.h>
using namespace std;
struct S{int x, y, d;};
map<char, S> d{{'R', {1,0,-1}}, {'L', {-1,0,-1}}, {'D', {0,-1,1}}, {'U', {0, 1,1}}};
int main(){
	string s; cin >> s; reverse(s.begin(), s.end());
	if(s.size()>2 && d[s[0]].d * d[s[1]].d + d[s[1]].d * d[s[2]].d == 2)
		return cout << "impossible\n",0;
	int x = 0, y = 0, p = 1, l = 'X';
	vector<S> ans;
	for(auto c : s)
		if(d[l].d != d[c].d){
			ans.push_back({x+d[c].x, y+d[c].y, 0});
			x -= p*d[c].x, y -= p*d[c].y;
			p*=2, l=c;
		}
	cout << x << ' ' << y << '\n' << ans.size() << '\n';
	for(auto p : ans) cout << p.x << ' ' << p.y << '\n';
}
