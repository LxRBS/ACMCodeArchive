struct ShortestPath_Dijkstra{

using weight_t = long long;

struct edge_t{
    int from;
    int to;
    weight_t w;
    edge_t(int a, int b, weight_t c):from(a),to(b),w(c){}
};

vector<vector<int>> g;
vector<edge_t> edges;

ShortestPath_Dijkstra():q([](const pair<int, weight_t> & a, const pair<int, weight_t> & b){
    if(a.second != b.second) return a.second > b.second;
    return a.first > b.first;
}){}

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

void Dijkstra(int s){
    int n = g.size() - 1;
    q.clear();
    d.assign(n + 1, inf());
    pre.assign(n + 1, 0);
    flag.assign(n + 1, 0);
    q.push({s, d[s] = 0});
    while(1){
        while(not q.empty() and flag[q.top().first]) q.pop();
        if(q.empty()) break;

        auto h = q.top(); q.pop();
        flag[h.first] = 1;

        int v;
        weight_t tmp;
        for(int i : g[h.first]){
            const auto & e = edges[i];
            if(flag[v = e.to] or d[v] <= (tmp = h.second + e.w)) continue;
            q.push({v, d[v] = tmp});
            pre[v] = h.first;
        }
    }
    return;
}

static weight_t inf() {
    static const weight_t INF = 0x7F8F9FAFBFCFDFEF;
    return INF;
}

__gnu_pbds::priority_queue<
    pair<int, weight_t>, 
    function<bool(const pair<int, weight_t> &, const pair<int, weight_t> &)>
> q;

vector<weight_t> d; // d[i]表示s到i的最短距离
vector<int> pre; // 从s到i的最短路径会经过pre[i]
vector<int> flag; // 标记数组

};