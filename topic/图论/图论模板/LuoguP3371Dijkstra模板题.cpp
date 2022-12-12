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
 

using llt = long long;
using weight_t = llt;
using vi = vector<int>;
using vvi = vector<vi>;

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
void mkDirectEdge(int a, int b, weight_t w=0){
    int t = this->edges.size();
    this->g[a].push_back(t);
    this->edges.push_back({a, b, w}); 
}

int node_cnt()const{return this->g.size()-1;}
int edge_cnt()const{return this->edges.size() / 2;}

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

}G;


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int n = getInt();
	int m = getInt();
	int s = getInt();
	G.init(n, m);
	for(int a,b,w,i=0;i<m;++i){
        a = getInt(); b = getInt();
		G.mkDirectEdge(a, b, w=getInt());
	}
	vector<llt> d;
	G.Dijkstra(s, d);
	for(int i=1;i<=n;++i) printf("%lld ", d[i]!=-1?d[i]:(1LL<<31)-1);
	printf("\n");
    return 0;
}