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
// 奇数编号的边是方向边，其前一条边是正向边
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
    printf("%lld\n", G.Dinic(s, t));
    return 0;
}