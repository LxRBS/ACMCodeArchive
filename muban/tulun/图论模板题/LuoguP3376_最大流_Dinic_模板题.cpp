#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_pbds;


namespace IO{

char *__abc147, *__xyz258, __ma369[1000000];
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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}

namespace TULUN{


struct NetworkMaxFlow_Dinic{

enum{INF=0x7F7F7F7F7F7F7F7F}; 

using llt = long long int;
using weight_t = llt;
using vi = vector<int>;
using vvi = vector<vi>;
using edge_t = tuple<int, int, weight_t>;

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
                if(get<2>(e) > 0 && -1 == level[v = get<1>(e)]){
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
            if(level[u] + 1 == level[v = get<1>(e)] && (c = get<2>(e)) > 0 && cf > tf){
                auto f = dfs(v, min(c, cf - tf));
                if(0 == f) continue;

                get<2>(e) -= f;
                get<2>(this->edges[i^1]) += f; // 反向边加f
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

}

int N, M, S, T;
TULUN::NetworkMaxFlow_Dinic Dinic;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
    N = getInt();
	M = getInt();
	S = getInt();
	T = getInt();
	Dinic.init(N, M);

    for(int a,b,w,i=0;i<M;++i){
		a = getInt(); b = getInt(); w = getInt();
		Dinic.mkDirectEdge(a, b, w);
	}

    auto ans = Dinic.Dinic(S, T);
	cout << ans << endl;
	return 0;
}