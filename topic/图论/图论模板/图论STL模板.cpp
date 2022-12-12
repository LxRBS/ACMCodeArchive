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


/// Dijkstra最短路，堆实现
struct ShortestPath_Dijkstra{

using llt = long long;
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
void mkDirectEdge(int a, int b, weight_t w){
    int t = this->edges.size();
    this->g[a].push_back(t);
    this->edges.push_back({a, b, w}); 
}

/**
 * @brief Dijkstra算法
 * @param s: 源点编号
 * @param d: di表示s到i的最短距离，输出参数
 */
void Dijkstra(int s, vector<weight_t> & d){    
    using piw = pair<int, weight_t>;
    int n = this->g.size();
    d.assign(n, -1);
    vector<bool> flag(n, false);
    /// 优先级队列，权值小的先出
    priority_queue<piw, vector<piw>, function<bool(const piw &, const piw &)>> q([](const piw & a, const piw & b)->bool{
        if(a.second != b.second) return a.second > b.second;
        return a.first > b.first;
    });
    q.push({s, d[s]=0});

    while(1){
        while(!q.empty() && flag[q.top().first]) q.pop();
        if(q.empty()) break;

        auto h = q.top(); q.pop();
        flag[h.first] = true;

        weight_t tmp;
        int v;
        for(int i : this->g[h.first]){
            const auto & e = this->edges[i];
            if(flag[v = e.to] || (d[v] < (tmp=e.w+h.second) && -1 != d[v])) continue;
            q.push({v, d[v] = tmp});
        }
    }
    return ;
}

};

/// 二分图，from和to都从1开始编号
struct BiGraphMaxMatch_HopcroftKarp{

enum{INF=2000000000};
using llt = long long;
using weight_t = llt;
using vi = vector<int>;
using vvi = vector<vi>;

struct edge_t{
    int from;
    int to;
};

vvi g;    // 邻接表
vector<edge_t> edges; // 边表

/// na表示A的点数，ecnt表示边数
void init(int na, int ecnt=0){
    this->g.assign(na + 1, vi());
    this->edges.clear();
    this->edges.reserve(ecnt);
}
/// a表示A中的节点，b表示B中的节点
void mkEdge(int a, int b){
    this->g[a].push_back(this->edges.size());
    this->edges.push_back({a, b});
}

/// na表示A的点数，nb表示B的点数，linka和linkb是输出参数
/// linka[i]表示Ai在B中匹配的序号的，即Ai与B[linka[i]]匹配
/// 同理A[linkb[i]]与Bi匹配
int HopcroftKarp(int na, int nb, vi & linka, vi & linkb){
    assert(na + 1 == this->g.size());
    linka.assign(na+1, 0);
    linkb.assign(nb+1, 0);

    vector<bool> flag(nb+1, false);
    vector<int> da(na+1, 0);
    vector<int> db(nb+1, 0);
    vector<int> q(na+1, 0);
    int dis = INF;

    auto bfs = [&](){
        fill(da.begin(), da.end(), 0);
        fill(db.begin(), db.end(), 0);

        auto head = q.begin();
        auto tail = q.begin();
        for(int i=1;i<=na;++i)if(!linka[i]) *tail++ = i; // 入队

        dis = INF;
        int u, v;
        while(head < tail){
            if(da[u = *head++] > dis) continue; // 出队
            
            for(auto i : this->g[u]){
                const auto & e = this->edges[i];
                if(0 == db[v = e.to]){
                    db[v] = da[u] + 1;
                    if(linkb[v]) {
                        da[*tail++ = linkb[v]] = db[v] + 1; // 入队
                    }else{
                        dis = db[v];
                    }
                }
            }
        }
        return dis < INF;
    };

    function<bool(int)> dfs = [&](int u)->bool{
        for(auto i : this->g[u]){
            const auto e = this->edges[i];
            auto v = e.to;
            if(!flag[v] && da[u] + 1 == db[v]){
                flag[v] = true;
                if(!linkb[v] || (db[v] != dis && dfs(linkb[v]))){
                    linka[linkb[v] = u] = v;
                    return true;
                }
            }  
        }
        return false;
    };

    int ret = 0;
    while(bfs()){
        fill(flag.begin(), flag.end(), false);
        for(int i=1;i<=na;++i){
            if(!linka[i]) ret += dfs(i);
        }
    }
    return ret;
}

};

/// 最大流Dinic算法，实现比较简单
struct NetworkMaxFlow_Dinic{

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

/// 返回s到t的最大流，具体方案通过查询方向边得到
weight_t Dinic(int s, int t){
    int n = this->g.size() - 1;
    vi level(n+1, 0);
    vi q(n + 1, 0);

    /// 广搜建立层次图
    auto bfs = [&]()->bool{
        fill(level.begin(), level.end(), -1);

        auto head = q.begin();
        auto tail = q.begin();
        int u, v;

        level[*tail++ = s] = 0; // 入队
        while(head < tail){
            for(auto i : this->g[u = *head++]){ // 出队
                const auto & e = this->edges[i];
                if(e.w > 0 && -1 == level[v=e.to]){
                    level[*tail++ = v] = level[u] + 1; // 入队
                }
            }
        }

        return -1 != level[t];
    };

    /// u是当前节点，cf是已经有的流
    function<weight_t(int, weight_t)> dfs = [&](int u, weight_t cf)->weight_t{
        if(u == t) return cf;

        weight_t tf = 0, c;
        int v;
        for(auto i : this->g[u]){
            auto & e = this->edges[i];
            if(level[u] + 1 == level[v=e.to] && (c = e.w) > 0 && cf > tf){
                auto f = dfs(v, min(c, cf - tf));
                if(0 == f) continue;

                e.w -= f;
                this->edges[i^1].w += f; // 反向边加f
                tf += f; 
            }
        }
        if(0 == tf) level[u] = -1;
        return tf;
    };

    weight_t ret = 0;
    while(bfs()){
        weight_t ans;
        while(ans = dfs(s, INF)){
            ret += ans;
        }
    }
    return ret;
}

};
/// 最大流，最高标号预流推进算法
/// 通过查询反向边得到方案
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

};

/// 强连通分量Tarjan算法
struct SCC_Tarjan{

using llt = long long;
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
}

int scccnt; // SCC的数量，序号从1开始
vi belong;  // belong[i]表示第i个顶点属于第belong[i]个scc
vi sccsize; // sccsize[i]表示第i个scc的尺寸

void Tarjan(){
    int n = this->g.size() - 1;
    this->belong.assign(n + 1, this->scccnt = 0);    
    this->sccsize.assign(n+1, 0);

    int timestamp = 0;

    vi st(n+1, 0); // 栈
    auto top = st.begin();
    
    vi low(n+1, 0);
    vi dfn(n+1, 0);
    vector<bool> isInStack(n+1, false);

    function<void(int)> dfs = [&](int u)->void{
        dfn[u] = low[u] = ++timestamp;
        isInStack[*top++ = u] = true; // 入栈

        int v;
        for(int i : this->g[u]){
            const auto & e = this->edges[i];
            if(0 == dfn[v = e.to]){
                dfs(v);
                if(low[v] < low[u]) low[u] = low[v];
            }else if(isInStack[v] && dfn[v] < low[u]){
                low[u] = dfn[v];
            }
        }

        /// 找到一个SCC
        if(dfn[u] == low[u]){
            ++scccnt;
            do{
                isInStack[v = *--top] = false;
                ++sccsize[belong[v] = scccnt]; 
            }while(v != u);
        }
        return;
    };

    for(int i=1;i<=n;++i){
        if(0 == dfn[i]){
            dfs(i);
        }
    }
    
    return;
}

vvi kdag; // KDAG，使用SCC的编号作为节点编号

/// Tarjan以后生成核心DAG
void getKDAG(){
    this->kdag.assign(this->scccnt+1, vi());
    int u, v;
    for(const auto & e : this->edges){
        if((u = this->belong[u]) != (v = this->belong[v])){
            kdag[u].push_back(v);
        }
    }
    return;
}

};

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    return 0;
}