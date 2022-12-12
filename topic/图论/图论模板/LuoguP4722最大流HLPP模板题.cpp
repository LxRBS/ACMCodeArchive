/**
 * 最大流HLPP算法，此题用Dinic和isap会超时
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2E5+5;
#endif

struct NetworkMaxFlow_HLPP{
enum{INF=0x7F7F7F7F7F7F7F7F}; 
using llt = long long int;
using weight_t = llt;
using vi = vector<int>;
using vvi = vector<vi>;

struct edge_t{
    int from;
    int to;
    weight_t w;
};

vvi g;    // 邻接表
vector<edge_t> edges; // 边表

void init(int ncnt, int ecnt=0){
    this->g.assign(ncnt+1, vi());
    this->edges.clear();
    this->edges.reserve(ecnt);
}

// 生成a到b的一条边，如果是无向图要连续调用该函数两次
// 奇数编号的边是反向边，其前一条边是正向边
void mkDirectEdge(int a, int b, weight_t w){
    int t = this->edges.size();
    this->g[a].push_back(t);
    this->edges.push_back({a, b, w}); 
    /// 生成反向边
    this->g[b].push_back(t+1);
    this->edges.push_back({b, a, 0});
}

weight_t hlpp(int s, int t){
	int n = this->g.size() - 1;
	int mxh, szh;
	
    vi h(n+1, 0);
	vi cnt(n+1, 0);
	vi q(n+1, 0); // 队列
	vvi vvs(n+1, vi());
	
	vector<list<int>> gap(n+1, list<int>());
	vector<list<int>::iterator> ep(n+1);

	vector<weight_t> flow(n+1, 0LL);
	flow[t] = -(flow[s] = INF);

	auto initLabel = [&]()->void{
		h.assign(n+2, n+2);

		auto head = q.begin();
		auto tail = q.begin();

		int u, v;

		h[*tail++ = t] = 0; // 入队
		while(head < tail){
			for(auto i : this->g[u = *head++]){
				const auto & e = this->edges[i];
                if(h[v=e.to] == n + 2 && this->edges[i^1].w != 0){
					++cnt[h[*tail++ = v] = h[u] + 1];
				}
			}
		}
		for(int i=0;i<=n;++i){
			gap[i].clear();
			vvs[i].clear();
		}
		for(int i=1;i<=n;++i){
		    if(h[i] > n) continue;

			ep[i] = gap[h[i]].insert(gap[h[i]].begin(), i);
			if(flow[i] > 0) vvs[h[i]].push_back(i);	
		}

        mxh = szh = h[*(tail - 1)];
	};

	auto pushEdge = [&](int u, int ei)->void{
		auto & e = this->edges[ei];
		int v = e.to;
        auto w = min(e.w, flow[u]);
		flow[u] -= w;
		e.w -= w;
		flow[v] += w;
		this->edges[ei^1].w += w;
		if(0 < flow[v] && flow[v] <= w){
            vvs[h[v]].push_back(v);
		}
	};

    auto push = [&](int u)->void{
        int v, fx = n + 1, tmp = h[u];
		for(int i : this->g[u]){
			const auto & e = this->edges[i];
			if(e.w <= 0) continue;

			if(h[v = e.to] + 1 == h[u]){
				pushEdge(u, i);
				if(!flow[u]) return;
			}else{
				fx = min(fx, h[v] + 1);
			}
		}
		if(cnt[h[u]] <= 1){
			for(int i=tmp;i<=mxh;gap[i].clear(),++i){
				for(int j : gap[i]){
					--cnt[h[j]];
					h[j] = n + 1;
				}
			}
			mxh = tmp - 1;
			return;
		}
		--cnt[tmp];
		ep[u] = gap[tmp].erase(ep[u]);
		h[u] = fx;
		if(n + 1 == fx) return;
		++cnt[fx];
        ep[u] = gap[fx].insert(gap[fx].begin(), u);
		mxh = max(szh = fx, mxh);
		vvs[fx].push_back(u);
	};

	h[s] = (cnt[0]=n) + 1;
	for(int i=1;i<=n;++i){
		if(i==s) continue;
		ep[i] = gap[h[i]].insert(gap[h[i]].begin(), i);
	}
	for(int i : this->g[s]){
		pushEdge(s, i);
	}
	initLabel();
	while(szh > 0){
		if(vvs[szh].empty()) {
		    --szh;
		}else{
            int x = vvs[szh].back();
			vvs[szh].pop_back();
			push(x);
		}
	}
	return flow[t] + INF;
}

}G;


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int n = getInt();
    int m = getInt();
    int s = getInt();
    int t = getInt();
    G.init(n, m);
    for(int a,b,w,i=0;i<m;++i){
        a = getInt(); b = getInt();
        G.mkDirectEdge(a, b, w = getInt());
    }
    printf("%lld\n", G.hlpp(s, t));
    return 0;
}