//std, 1003
#include<bits/stdc++.h>
using namespace std;
int n, m, now;
char mp[10][10];
vector<pair<int, int> > seq;
vector<long long> st[105];
inline int Id(int x, int y) {
	return x * m + y;
}
inline int Check() {
	for(int l = 0, r = (int)seq.size() - 1; l < r; ++ l, -- r)
		if(mp[seq[l].first][seq[l].second] != mp[seq[r].first][seq[r].second])
			return 0;
	return 1;
}
inline void Solve(int x, int y, long long s) {
// cerr << s << endl;
	// if(seq.size() > n)
	// 	return;
	if(Check())
		st[now].push_back(s);
	if(x < n - 1) {
		seq.push_back(make_pair(x + 1, y));
		Solve(x + 1, y, s | (1ll << (Id(x + 1, y))));
		seq.pop_back();
	}
	if(y < m - 1) {
		seq.push_back(make_pair(x, y + 1));
		Solve(x, y + 1, s | (1ll << (Id(x, y + 1))));
		seq.pop_back();
	}
}
int T, tot, C;
map<long long, int> id;
long long all, ans[3000005];
inline long long Mark(long long s) {
// cerr << s << " " << id[s] << " " << ans[id[s]] << endl;
	if(s == all)
		return 1;
	if(id[s])
		return ans[id[s]];
	id[s] = ++ tot;
	int p = __builtin_ctzll(~s), now = tot;
	ans[now] = 0;
	for(auto nxt : st[p])
		if(!(nxt & s)) {
// cerr << "? " << nxt << " " << s << " " << p << endl;
			ans[now] += Mark(s | nxt);
		}
	return ans[now];
}
int main() {
	for(scanf("%d", &T); T --; ) {
		// printf("Case #%d: ", ++ C);
		tot = 0, all = 0;
		id.clear();
		scanf("%d%d", &n, &m);
// cerr << " n = " << n << " m = " << m << endl;
		for(int i = 0; i < n; ++ i)
			scanf("%s", mp[i]);
		// long long pathtot = 0;
		for(int i = 0; i < n; ++ i)
			for(int j = 0; j < m; ++ j) {
				st[Id(i, j)].clear();
				seq.clear();
				seq.push_back(make_pair(i, j));
				now = Id(i, j);
				Solve(i, j, 1ll << now);
// cerr << i << ", " << j << endl;
// for(auto x : st[Id(i, j)])
// 	cerr << x << endl;
// cerr << i << " " << j << " " << now << endl;
				// pathtot += st[now].size();
				all |= 1ll << now;
			}
// cerr << all << endl;
		// printf("%lld\n", pathtot);
		printf("%lld\n", Mark(0));
		// cerr << tot << endl;
		for(int i = 0; i <= tot; ++ i)
			ans[i] = 0;
	}
}