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

int N, M;
ShortestPath_SPFA SPFA;

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = 1; 
    cin >> nofkase;
    while(nofkase--){
        cin >> N >> M;
        SPFA.init(N, M);
        for(int i=0;i<M;++i){
            int a, b, c;
            cin >> a >> b >> c;
            SPFA.mkDiEdge(a, b, c);
            if(c >= 0) SPFA.mkDiEdge(b, a, c);
        }
        bool b = SPFA.spfa(1);
        cout << (b ? "NO" : "YES") << endl;
    }
    

    return 0;
}