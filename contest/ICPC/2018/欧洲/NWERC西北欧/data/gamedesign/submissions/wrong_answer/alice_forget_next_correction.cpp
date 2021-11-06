#include <bits/stdc++.h>


#define all(c) (c).begin(),(c).end()
#define pb push_back
#define sz(c) ll((c).size())
#define FOR(i,a,b) for(ll i=(a); i<(b); i++)
#define FORD(i,a,b) for(ll i=(b-1); i>=(a); i--)
#define xx first
#define yy second

using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;

int main(){
	string s;
	cin >> s;

	if(sz(s) >= 3){
		string rest = s.substr(sz(s)-3, 3);
		set<string> impos = {"UDU", "DUD", "LRL", "RLR"};
		if(impos.find(rest) != impos.end()){
			cout << "impossible" << endl;
			return 0;
		}
	}

	set<pll> res;

	ll x = 0;
	ll y = 0;

	map<char, pll> dirs;
	dirs['U'] = {0, 1}; dirs['D'] = {0, -1}; dirs['L'] = {-1, 0}; dirs['R'] = {1, 0};

	FOR(i, 0, sz(s)){
		char c = s[i];
		pll next;
		FOR(k, 0, 1 << (i+1)){
			next = {x + dirs[c].xx, y + dirs[c].yy};
			if(res.find(next) != res.end()){
				break;
			}
			tie(x, y) = next;
		}
		res.insert(next);
	}

	cout << -x << " " << -y << endl;
	cout << sz(res) << endl;
	for(auto& r : res){
		cout << r.xx - x << " " << r.yy - y << endl;
	}

}
