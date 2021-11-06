#include <bits/stdc++.h>

#define all(c) (c).begin(),(c).end()
#define pb push_back
#define sz(c) ll((c).size())
#define FOR(i,a,b) for(ll i=(a); i<(b); i++)
#define FORD(i,a,b) for(ll i=(b-1); i>=(a); i--)

using namespace std;

typedef long long ll;
typedef vector<ll> vl;

int main(){
	ll n;
	cin >> n;
	vl ps(n);
	for(auto& p : ps) cin >> p;

	ll mx = -1;
	FOR(i, 1, n) mx = max(mx, ps[i]);
	ll res = 0;

	ll g1 = 0;
	ll g2 = 0;
	multiset<ll> g3;
	ll go3 = 0;

	FOR(i, 1, n){
		if(ps[i] == mx) g1++;
		else if (ps[i] == mx-1) g2++;
		else g3.insert(mx-ps[i]);
	}

	while(ps[0] >= mx){
		if(g1 >= 2){
			ll down = g1 / 2;
			g1 -= down;
			g2 += down;
			mx++;
		} else {
			go3++;
			g1 += g2;
			g2 = 0;
			while(sz(g3) && *g3.begin() == go3+1){
				g3.erase(g3.begin());
				g2++;
			}
		}

		res++;
	}

	cout << res - 1 << endl;

	return 0;
}
