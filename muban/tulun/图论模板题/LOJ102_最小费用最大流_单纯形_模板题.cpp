#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

struct CostFlow_Simplex{ // 费用流单纯形

using weight_t = long long;
/// 要使用链表形式，因为过程中有一个边交换的操作
/// 否则就需要交换指针
struct edge_t{ 
    int from;
	int to;
	weight_t cap;
	weight_t cost;
    int next;
	edge_t(int a,int b,weight_t c,weight_t d,int e):from(a),to(b),cap(c),cost(d),next(e){}
};
vector<int> g;
vector<edge_t> edges;

void init(int n, int m){
	g.assign(n + 1, 0);
	edges.clear();
	edges.reserve(m + 1 << 1);
    /// 边链表一律从2开始保存
    edges.push_back({0, 0, 0, 0, 0});
    edges.push_back({0, 0, 0, 0, 0});
}

void mkDirectEdge(int a, int b, weight_t cap, weight_t cost){
	auto t = edges.size();
	edges.push_back({a, b, cap, cost, g[a]});
	edges.push_back({b, a, 0, -cost, g[b]});
    g[b] = (g[a] = t) ^ 1;
}

pair<weight_t, weight_t> mcmf(int s, int t){
	auto n = g.size() - 1;
    S = s, T = t;
	miniCost = maxFlow = 0;
	flag.assign(n + 1, 0);
	father.assign(n + 1, 0);
	fae.assign(n + 1, 0);
	cache.assign(n + 1, 0);
	cyc.assign(edges.size() + 1, 0);
    /// 首先加一条边
	mkDirectEdge(T, S, inf(), -costInf());
	/// 初始化树结构
	dfs(T);
	flag[T] = timestamp = 2;
	while(1){
		bool b = true;
        for(int i=2,n=edges.size();i<n;++i){
			auto & e = edges[i];
			if(e.cap != 0 and e.cost + phi(e.to) < phi(e.from)){
                b = false;
				miniCost += pushFlow(i);
			}
		}
		if(b) break;
	}
	maxFlow = edges.back().cap;
	return {maxFlow, miniCost += maxFlow * costInf()};
}

weight_t pushFlow(int ei){
	auto & e = edges[ei];
	int rt = e.from;
	int lca = e.to;
	++timestamp;
	while(rt) flag[rt] = timestamp, rt = father[rt];
	while(flag[lca] != timestamp) flag[lca] = timestamp, lca = father[lca];

	/// 找到边，记录最小
	weight_t flow = e.cap;
	int cidx = 0, path = 2, delu = 0;
	for(int u=e.from;u!=lca;u=father[u]){
		if(edges[cyc[++cidx] = fae[u]].cap < flow){
            flow = edges[fae[delu = u]].cap;
            path = 0;
		}
	}
	for(int u=e.to;u!=lca;u=father[u]){        
		if(edges[cyc[++cidx] = fae[u] ^ 1].cap < flow){
            flow = edges[fae[delu = u] ^ (path = 1)].cap;
		}
	}
	cyc[++cidx] = ei;
	/// 沿着环推流
	weight_t cost = 0;
	for(int i=1;i<=cidx;++i){
		cost += edges[cyc[i]].cost * flow;
        edges[cyc[i]].cap -= flow;
		edges[cyc[i] ^ 1].cap += flow;		
	}
	if(2 == path) return cost;
	/// 加边到树，翻转链
    int lastei = ei ^ path;
    int lastu = edges[lastei].to;
    int now = edges[lastei].from;
	while(lastu != delu){
		lastei ^= 1;
		--flag[now];
		swap(lastei, fae[now]);
		swap(lastu, father[now]);
		swap(lastu, now);
	}
	return cost;
}

weight_t phi(int u){
    if(flag[u] == timestamp) return cache[u];
	return flag[u] = timestamp, cache[u] = phi(father[u]) - edges[fae[u]].cost;
}

void dfs(int u){
    flag[u] = 1;
	for(int v,i=g[u];i;i=edges[i].next){
		auto & e = edges[i];
		if(not flag[v = e.to] and e.cap != 0){
            father[v] = u;
			fae[v] = i;
			dfs(v);
		}
	}
	return;
}

static weight_t inf() {
	static const weight_t INF = 1E13;
	return INF;
}

/// costINF和cap有一个乘法操作，注意溢出
static weight_t costInf(){
	static const weight_t INF = 0x3f3f3f3;
	return INF;
}

int S, T;
vector<int> father; // father[i]是i的父亲
vector<int> fae; // fae[i]是father[i]到i的边
vector<int> flag;
vector<int> cyc;
vector<weight_t> cache; 

int timestamp;
weight_t miniCost;
weight_t maxFlow;

};

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m, s, t;
	cin >> n >> m;
	s = 1, t = n;
	CostFlow_Simplex ssp;
	ssp.init(n, m);
	for(int a,b,c,d,i=0;i<m;++i){
		cin >> a >> b >> c >> d;
		ssp.mkDirectEdge(a, b, c, d);
	}
	auto ans = ssp.mcmf(s, t);
	cout << ans.first << " " << ans.second << endl;
    return 0;
}