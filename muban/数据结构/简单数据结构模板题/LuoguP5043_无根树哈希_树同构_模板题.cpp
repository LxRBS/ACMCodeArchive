#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 101;
#else
int const SZ = 1E5+1;
#endif

struct TreeHash{ // 无根树哈希

size_t hash(int rt) {
    dfs(rt, 0);
	rh[rt] = h[rt];
	dfs2(rt, 0);
	size_t ans = 1;
	for(int i=1,n=tree.size();i<n;++i) ans += shift(rh[i]);
	return ans;
}

TreeHash
(
	const vector<vector<int>> & t,
	size_t s = 0
):tree(t),seed(s?s:std::chrono::steady_clock::now().time_since_epoch().count())
, h(t.size(), 0), rh(t.size(), 0){}

void dfs2(int u, int p) {
	for(int v : tree[u]){
		if(v == p) continue;
		rh[v] = h[v] + shift(rh[u] - shift(h[v]));
		dfs2(v, u);
	}
	return;
}

void dfs(int u, int p) {
    h[u] = 1;
	for(auto v : tree[u]){
		if(v == p) continue;
		dfs(v, u);
		h[u] += shift(h[v]);
	}
	return;
}

size_t shift(size_t x){
	x ^= seed;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	x ^= seed;
	return x;
}

const vector<vector<int>> & tree;
const size_t seed;
vector<size_t> h;
vector<size_t> rh;

};

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
	int m;
    cin >> m;
	map<size_t, int> ss;
	for(int i=1;i<=m;++i){
        int n; cin >> n;
		vvi tree(n + 1);
		int rt = 0;
		for(int p,i=1;i<=n;++i){
            cin >> p;
			if(0 == p) {rt = i; continue;}
			tree[p].push_back(i);
		}
		assert(rt);
		TreeHash th(tree, seed);
        auto h = th.hash(rt);
		auto it = ss.find(h);
		if(it == ss.end()) it = ss.insert(it, {h, i});
		cout << it->second << endl;
	}
    return 0;
}