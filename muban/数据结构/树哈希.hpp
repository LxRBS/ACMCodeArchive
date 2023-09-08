struct RootTreeHash{ // 有根树哈希

size_t hash(int r){
	dfs(r, 0);
	return h[r];
}

void dfs(int u, int p) {
    h[u] = 1;
	for(auto v : tree[u]){
		if(v == p) continue;
		dfs(v, u);
		h[u] += shift(h[v]);
	}
}

RootTreeHash(const vector<vector<int>> & t, size_t s=0)
:tree(t),seed(s?s:std::chrono::steady_clock::now().time_since_epoch().count()),h(t.size())
{}

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
vector<size_t> h; // 1-index

};


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
