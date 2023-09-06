/**
 * 二分图最大匹配给方案
 * 
 */
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

struct Match_HopcroftKarp{

using vi = vector<int>;
using weight_t = int; // 一般不会用到边权

struct edge_t{
    int from;
    int to;
    weight_t w;
    edge_t(int a, int b, weight_t c):from(a),to(b),w(c){}
};

/// 二分图，该图里其实只有A部分的节点
vector<vector<int>> g;
///第0条边表示空，真正的边从下标1开始
vector<edge_t> edges;

/// 初始化A部分的点数即可
void init(int na, int m){
    g.assign(na + 1, {});
    edges.clear();
    edges.reserve(m + 1);
    edges.push_back({0, 0, 0});
}

void mkDiEdge(int a, int b, weight_t c=0){
    g[a].push_back(edges.size());
    edges.push_back({a, b, c});
}

/// LinkAi is the matched edge of Ai 
/// LinkBi is the matched edge of Bi
/// so LinkB[Edge[LinkA[i]].from] = Ai  
/// and LinkA[Edge[LinkB[i]].to]] = Bi
/// 某个linki == 0，说明i不在当前匹配上
vi linka; 
vi linkb;

//na是A的数量，nb是B的数量
int HopcroftKarp(int na, int nb){
    assert(g.size() - 1 == na);
    linka.assign(na + 1, 0);
    linkb.assign(nb + 1, 0);
    flag.assign(nb + 1, 0);
    da.assign(na + 1, 0);
    db.assign(nb + 1, 0);
    q.assign(na, 0);

    int ret = 0;
    while(bfs(na, nb)){
        fill(flag.begin(), flag.end(), 0);
        for(int i=1;i<=na;++i){
            if(not linka[i]){
                ret += dfs(i);
            }
        }
    }
    return ret;
}

bool bfs(int na, int nb){
    fill(da.begin(), da.end(), 0);
    fill(db.begin(), db.end(), 0);

    auto head = q.begin(), tail = q.begin();
    for(int i=1;i<=na;++i)if(not linka[i]) *tail++ = i;

    _dis = inf();
    int u, v;
    while(head < tail){
        if(_dis < da[u = *head++]) continue;
        for(auto i : g[u]){
            const auto & e = edges[i];
            if(0 == db[v = e.to]){
                db[v] = da[u] + 1;
                if(linkb[v]) da[*tail++ = edges[linkb[v]].from] = db[v] + 1;
                else _dis = db[v];
            }
        }
    }
    return _dis < inf();
}

bool dfs(int u){
    int v;
    for(auto i : g[u]){
        const auto & e = edges[i];
        if(not flag[v = e.to] and db[v] == da[u] + 1){
            flag[v] = 1;
            if(not linkb[v] or (db[v] != _dis and dfs(edges[linkb[v]].from))){
                linka[edges[linkb[v] = i].from] = i;
                return true;
            }
        }
    }
    return false;
}

static int inf() {
    static const int INF = 0x7F8F9FAF;
    return INF;
}

vi flag;
vi da, db; // 辅助数组
vi q; // 辅助队列
int _dis; // 辅助数据

};

int NA, NB, M;
Match_HopcroftKarp Match;

void proc(){
    auto ans = Match.HopcroftKarp(NA, NB);
    cout << ans << endl;
    for(int i=1;i<=NA;++i){
        cout << Match.edges[Match.linka[i]].to << " ";
    }
    cout << endl;
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> NA >> NB >> M;
    Match.init(NA, M);
    for(int a,b,i=0;i<M;++i){
        cin >> a >> b;
        Match.mkDiEdge(a, b);
    }
    proc();
    return 0;
}