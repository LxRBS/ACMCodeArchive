struct ShortestPath_SPFA{

using weight_t = long long;

struct edge_t{
    int from;
    int to;
    weight_t w;
    edge_t(int a, int b, weight_t c):from(a),to(b),w(c){}
};

vector<vector<int>> g;
vector<edge_t> edges;

void init(int n, int m){
    g.assign(n + 1, {});
    edges.clear();
    edges.reserve(m);
}

void mkDiEdge(int a, int b, int c){
    g[a].emplace_back(edges.size());
    edges.push_back({a, b, c});    
}

void mkBiEdge(int a, int b, int c){
    mkDiEdge(a, b, c);
    mkDiEdge(b, a, c);
}

/// 返回false表示从s出发能到达负环，返回true表示有最短路
bool spfa(int s){
    int n = g.size() - 1;
    while(not q.empty()) q.pop();
    d.assign(n + 1, inf());
    flag.assign(n + 1, 0);
    cnt.assign(n + 1, 0);
    q.push(s);
    flag[s] = true;
    d[s] = 0;
    cnt[s] = 1;
    while(not q.empty()){
        auto h = q.front(); q.pop();
        flag[h] = 0;
        
        int v;
        weight_t tmp;
        for(int i : g[h]){
            const auto & e = edges[i];   
            if((tmp = d[h] + e.w) < d[v = e.to]){
                d[v] = tmp;
                if(0 == flag[v]){
                    flag[v] = 1;
                    q.push(v);
                    if(++cnt[v] > n){
                        return false;
                    }
                }
            }  
        }
    }
    return true;
}

static weight_t inf() {
    static const weight_t INF = 0x7F8F9FAFBFCFDFEF;
    return INF;
}


queue<int> q;
vector<weight_t> d; // d[i]表示s到i的最短距离
vector<int> pre; // 从s到i的最短路径会经过pre[i]
vector<int> flag; // 标记数组
vector<int> cnt; // 入队次数

};