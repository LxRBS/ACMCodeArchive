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

}G;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int na = getInt(); 
    int nb = getInt();
    int m = getInt();
    G.init(na, m);
    for(int a,b,i=0;i<m;++i){
        a = getInt(); b = getInt();
        G.mkEdge(a, b);
    }
    BiGraphMaxMatch_HopcroftKarp::vi linka, linkb;
    int ans = G.HopcroftKarp(na, nb, linka, linkb);
    printf("%d\n", ans);
    for(int i=1;i<=na;++i)printf("%d ", linka[i]);
    printf("\n");
    return 0;
}