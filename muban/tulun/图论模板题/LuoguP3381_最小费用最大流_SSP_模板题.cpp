/**
 * 最小费用最大流模板题
 * Dinic深搜扩流
 * UOJ487 45分
 * 9AC，3WA，7WA
 */
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
int const SZ = 110;
#endif

struct CostFlow_SSP{

using weight_t = long long;
struct edge_t{
    int from;
	int to;
	weight_t cap;
	weight_t cost;
	edge_t(int a,int b,weight_t c,weight_t d):from(a),to(b),cap(c),cost(d){}
};
vector<vector<int>> g;
vector<edge_t> edges;

void init(int n, int m){
	g.assign(n + 1, {});
	edges.clear();
	edges.reserve(m << 1);
}

void mkDirectEdge(int a, int b, weight_t cap, weight_t cost){
	auto t = edges.size();
	g[a].push_back(t);
	g[b].push_back(t ^ 1);
	edges.push_back({a, b, cap, cost});
	edges.push_back({b, a, 0, -cost});
}

pair<weight_t, weight_t> mcmf(int s, int t){
	auto n = g.size() - 1;
	dis.assign(n + 1, 0);
	flag.assign(n + 1, 0);
    S = s, T = t;
	minCost = maxFlow = 0;
	weight_t tmp;
	while(spfa())while(tmp = dfs(S, inf()))maxFlow += tmp;
	return {maxFlow, minCost};
}

bool spfa(){
	fill(flag.begin(), flag.end(), 0);
	fill(dis.begin(), dis.end(), inf());
    queue<int> q;
	q.push(S);
	dis[S] = 0;
	flag[S] = 1;
	while(not q.empty()){
		auto h = q.front(); q.pop();
		flag[h] = 0;
        int v;
		weight_t tmp;
		for(int i : g[h]){
            auto & e = edges[i];
			if(e.cap > 0 and (tmp = dis[h] + e.cost) < dis[v = e.to]){
                dis[v] = tmp;
				if(not flag[v]) q.push(v), flag[v] = 1;
			}
		}
	}
	return dis[T] != inf();
}

weight_t dfs(int u, weight_t cf){
	if(u == T) return cf;
	flag[u] = 1;
	weight_t ans = 0;
	int v;
    for(int i : g[u]){
		if(cf <= ans) break;
		auto & e = edges[i];
		if(not flag[v = e.to] and e.cap > 0 and dis[v] == dis[u] + e.cost){
			auto x = dfs(v, min(e.cap, cf - ans));
			if(x){
                minCost += x * e.cost;
				e.cap -= x;
				edges[i ^ 1].cap += x;
				ans += x;
			}
		}
	}
	flag[u] = 0;
	return ans;
}

static weight_t inf() {
	static const weight_t INF = 0x7F8F9FAFBFCFDFEF;
	return INF;
}

int S, T;
vector<int> flag;
vector<weight_t> dis;
weight_t minCost, maxFlow;

};

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m, s, t;
	cin >> n >> m >> s >> t;
	CostFlow_SSP ssp;
	ssp.init(n, m);
	for(int a,b,c,d,i=0;i<m;++i){
		cin >> a >> b >> c >> d;
		ssp.mkDirectEdge(a, b, c, d);
	}
	auto ans = ssp.mcmf(s, t);
	cout << ans.first << " " << ans.second << endl;
    return 0;
}