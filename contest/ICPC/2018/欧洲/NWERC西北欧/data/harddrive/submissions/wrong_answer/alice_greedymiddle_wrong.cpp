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
	ll n, e, b;
	cin >> n >> e >> b;
	//cerr << n << " " << e << " " << b << endl;
	string erg(n, 'x');
	//cerr << erg << endl;
	vl fixed_zeros(b);
	FOR(i, 0, b){
		ll l;
		cin >> l;
		l--;
		fixed_zeros[i] = l;
		erg[l] = '0';
	}
	sort(all(fixed_zeros));

	//cerr << erg << endl;

	FOR(i, 0, sz(fixed_zeros)-1){
		ll fr = fixed_zeros[i];
		ll to = fixed_zeros[i+1];

		for(ll x = fr+1; x < to; x += 2){
			if(e > 1){
				erg[x] = '1';
				erg[x+1] = '0';
				e -= 2;
			} else {
				erg[x] = erg[x+1] = '0';
			}
		}
	}

	//cerr << erg << endl;

	FOR(i, fixed_zeros[0]-(e/2)*2, fixed_zeros[0]){
		erg[i] = '1';
		erg[i+1] = '0';
	}
	//cerr << erg << endl;

	FOR(i, 0, fixed_zeros[0]-(e/2)*2){
		erg[i] = e % 2 ? '1' : '0';
	}

	cout << erg << endl;

	return 0;
}
