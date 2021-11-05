#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>
#include <climits>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
typedef long long ll;
int N, P, R, pts[5005], n, slots[5005], nxt[5005];
set<int> coords;
unordered_map<int,int> cmp, rev;

ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a%b); }

int nxt_free(int id) {
	if (slots[id]) return id;
	if (nxt[id] != id) return nxt[id] = nxt_free(nxt[id]);
	return nxt[id] = nxt_free((id + 1) % n);
}

int main() {
	cin >> N >> P >> R;
	FOR(i,0,N) {
		cin >> pts[i];
		coords.insert(pts[i]);
	}
	for(auto i : coords) {
		cmp[i] = n++;
		rev[cmp[i]] = i;
	}
	
	n = coords.size();
	ll maxi = -1, mini = LLONG_MAX, tot = 0;
	FOR(i,0,n) {
		int cur = rev[i];
		FOR(j,0,n) slots[j] = 0;
		FOR(j,0,N) slots[cmp[pts[j]]]++;
		FOR(j,0,n) nxt[j] = j;
		ll time = 0;
		FOR(j,0,N) {
			int last = cur;
			auto it = coords.upper_bound(cur-1);
			if (it == coords.end()) it = coords.begin();
			cur = *it;
			cur = rev[nxt_free(cmp[cur])];
			time += (P + cur - last) % P;
			slots[cmp[cur]]--;
			time += R;
			cur = (cur + R)%P;
		}
		ll strike = (P + rev[i] - rev[(i+n-1)%n]) % P;
		if (strike == 0) strike = P;
		mini = min(mini, time);
		maxi = max(maxi, time + strike - 1);
		tot += (time * strike + strike*(strike-1)/2);
	}
	cout << mini << endl << maxi << endl;
	ll ggt = gcd(tot,P);
	cout << tot/ggt << "/" << P/ggt << endl;
	
	return 0;
}
