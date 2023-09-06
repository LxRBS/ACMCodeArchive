#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 101;
#else
int const SZ = 110;
#endif



struct MaxFlow_Dinic{


using weight_t = long long;

struct edge_t{
    int from;
    int to;
    weight_t w;
    edge_t(int a, int b, weight_t c):from(a),to(b),w(c){}
};

vector<vector<int>> g; // 从1开始编号
vector<edge_t> edges; // 边表

void init(int ncnt, int ecnt=0){
    this->g.assign(ncnt+1, vi());
    this->edges.clear();
    this->edges.reserve(ecnt);
}

// 生成a到b的一条边，如果是无向图要连续调用该函数两次
// 奇数编号的边是反向向边，其前一条边是正向边
void mkDirectEdge(int a, int b, weight_t w){
    int t = this->edges.size();
    this->g[a].push_back(t);
    this->edges.push_back({a, b, w}); 
    /// 生成反向边
    this->g[b].push_back(t+1);
    this->edges.push_back({b, a, 0});
}

/// 返回s到t的最大流，具体方案通过查询方向边得到
weight_t maxflow(int s, int t){
    int n = this->g.size() - 1;
    level.assign(n + 1, 0);
    q.assign(n + 1, 0);
    S = s, T = t;

    weight_t ret = 0;
    while(bfs()){
        weight_t ans;
        while(ans = dfs(s, inf())){
            ret += ans;
        }
    }
    return ret;
}

/// 建立层次图
bool bfs(){
    fill(level.begin(), level.end(), -1);

    auto head = q.begin();
    auto tail = q.begin();
    int u, v;

    level[*tail++ = S] = 0;
    while(head < tail){
        for(auto i : g[u = *head++]){
            const auto & e = edges[i];
            if(e.w > 0 and -1 == level[v = e.to]){
                level[*tail++ = v] = level[u] + 1;
            }
        }
    }

    return -1 != level[T];
}

/// 从当前节点u开始深搜
weight_t dfs(int u, weight_t cf){
    if(u == T) return cf;

    weight_t tf = 0, c;
    int v;
    for(auto i : g[u]){
        auto & e = edges[i];
        if(level[u] + 1 == level[v = e.to] and 0 < (c = e.w) and tf < cf){
            auto f = dfs(v, min(c, cf - tf));
            if(0 == f) continue;

            e.w -= f;          // 正向边减
            edges[i ^ 1].w += f; // 反向边加
            tf += f;
        }
    }
    if(0 == tf) level[u] = -1;
    return tf;
}

static weight_t inf() {
    static const weight_t INF = 0x7F8F9FAFBFCFDFEF;
    return INF;
}

/// 对每一条使用了流的边调用函数f
void forEachUsed(function<void(int index, weight_t usedw)> f){
    for(int i=1,n=edges.size();i<n;i+=2){
        if(edges[i].w > 0){ // 反向边为正，说明正向边用了这么多流
            f(i ^ 1, edges[i].w);
        }
    }
    return;
}

vector<int> level; // 层次图
vector<int> q; // 队列
int S, T; // 源汇

};

int K, N;
int M;
MaxFlow_Dinic Dinic;

void proc(){
    auto ans = Dinic.maxflow(N + K + 1, N + K + 2);
    if(ans != M) return (void)(cout << "No Solution!" << endl);

    vvi results(K + 1, vi());
    Dinic.forEachUsed([&](int index, MaxFlow_Dinic::weight_t usedw){
        const auto & e = Dinic.edges[index];
        if(1 <= e.from and e.from <= K and K + 1 <= e.to and e.to <= N + K){
            assert(e.w == 0 and usedw == 1);
            results[e.from].push_back(e.to - K);
        }
    });
    for(int i=1;i<=K;++i){
        sort(results[i].begin(), results[i].end());
        cout << i << ":";
        for(int j : results[i]) cout << " " << j;
        cout << endl;
    }
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> K >> N;

    M = 0;
    Dinic.init(N + K + 2);
    for(int a,i=1;i<=K;++i){
        cin >> a;
        Dinic.mkDirectEdge(N + K + 1, i, a);
        M += a;
    }
    
    for(int i=1;i<=N;++i){
        int p; cin >> p;
        for(int type,j=0;j<p;++j){
            cin >> type;
            Dinic.mkDirectEdge(type, K + i, 1);
        }
        Dinic.mkDirectEdge(K + i, N + K + 2, 1);
    }

    proc();
    return 0;
}