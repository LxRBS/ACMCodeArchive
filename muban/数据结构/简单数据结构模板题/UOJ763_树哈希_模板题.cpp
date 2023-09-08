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

struct RootTreeHash{

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

RootTreeHash(const vector<vector<int>> & t)
:tree(t),seed(std::chrono::steady_clock::now().time_since_epoch().count()),h(t.size())
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

int N;
vvi Tree;

int proc(){
	RootTreeHash th(Tree);
	th.hash(1);
    set<size_t> ss;
	for(int i=1;i<=N;++i) ss.insert(th.h[i]);
	return ss.size();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N;
	Tree.assign(N + 1, {});
	for(int a,b,i=1;i<N;++i){
        cin >> a >> b;
		Tree[a].push_back(b);
		Tree[b].push_back(a);
	}
	cout << proc() << endl;
    return 0;
}