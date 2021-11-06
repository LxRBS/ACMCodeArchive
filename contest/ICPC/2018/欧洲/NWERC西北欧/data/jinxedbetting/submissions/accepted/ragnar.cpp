#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	int n; cin >> n;
	ll T, steps = 0; cin >> T;
	map<ll,int> s;
	while(--n){ ll x; cin >> x; ++s[x]; }
	while(true){
		auto& h = *prev(end(s)); auto k = h.second;
		if(h.first == T && h.second > 1) return cout << steps << endl, 0;
		ll x = 32-__builtin_clz(k);
		ll t = min(h.second == 1 ? ll(1e18) : (T-h.first)*x/(x-1),
				s.size() == 1 ? ll(1e18) : (h.first - prev(prev(end(s)))->first)*x);
		T-=t, steps += t;
		if(t < x){
			s[h.first] -= k - k >> t%x;
			s[h.first-1] += k - k >> t%x;
			auto after = s[h.first] + s[h.first-1];
		} else {
			if(    k >> t%x) s[h.first - t/x  ] += k >> t%x;
			if(k - k >> t%x) s[h.first - t/x-1] += k - k >> t%x;
			s.erase(prev(end(s)));
		}
	}
}
