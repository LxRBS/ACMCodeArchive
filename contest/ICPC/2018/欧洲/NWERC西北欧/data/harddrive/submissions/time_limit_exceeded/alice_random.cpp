#include <bits/stdc++.h>

#define all(c) (c).begin(),(c).end()
#define pb push_back
#define xx first
#define yy second
#define FOR(i,a,b) for(ll i=(a); i<(b); i++)

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<pair<ll,ll>> vpll;

ll const CPU_FREQ = 200000000;
ll const SEC = 1;

int main(){
	ll n, e, b;
	cin >> n >> e >> b;
	string erg(n, '?');
	FOR(i, 0, b){
		ll l;
		cin >> l;
		erg[l-1] = '0';
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 1);

	while(1){
		string tmp = erg;
		FOR(i, 0, n){
			if(tmp[i] == '0') continue;
			tmp[i] = '0' + dis(gen);
		}
		ll sm = 0;
		FOR(i, 0, n-1){
			sm += abs(tmp[i+1]-tmp[i]);
		}
		if(sm == e){
			cout << tmp << endl;
			break;
		}
	}

	return 0;
}
