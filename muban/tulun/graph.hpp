#include <bits/stdc++.h>
using namespace std;

namespace TULUN{

struct Graph{

using vi = vector<int>;
using vvi = vector<vi>;
using weight_t = int;
using edge_t = tuple<int, int, weight_t>;
using ve = vector<edge_t>;

vvi g;    // 邻接表，从1开始编号
ve edges; // 边表，从0开始编号

/// 如果是无向图，edgecnt需要等于题目给定边数的两倍
void init(int nodecnt, int edgecnt){
    g.assign(nodecnt + 1, vi());
    edges.reserve(edgecnt);
}
/// 单向边
void mkOneEdge(int a, int b, weight_t w){    
    g[a].emplace_back(edges.size());
    edges.emplace_back(a, b, w);
}
/// 双向边
void mkBiEdges(int a, int b, weight_t w){
    mkOneEdge(a, b, w);
    mkOneEdge(b, a, w);
}

int node_size() const {return g.size() - 1;}

const vi & operator [] (int pos) const {return g[pos];}

};


}