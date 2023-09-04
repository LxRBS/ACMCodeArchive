/**
 * 求大于1的SCC的数量
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


struct SCCTarjan{

using weight_t = int; // 权值类型
using vi = vector<int>;

struct edge_t{
    int from;
    int to;
    weight_t w;
    edge_t(int a, int b, weight_t c):from(a),to(b),w(c){}
};

vector<edge_t> edges;
vector<vi> g;

SCCTarjan() = default;

/// 点数和边数
void init(int n, int m){
    g.assign(n + 1, vi());
    edges.clear();
    edges.reserve(m);
}

/// a到b建一条有向边
void mkDiEdge(int a, int b, weight_t w = 0){    
    g[a].emplace_back(edges.size());
    edges.emplace_back(edge_t(a, b, w));
}


int SCCCnt; // 连通分量的总数
vi Belong;  // 第i个定点属于第Belong[i]个SCC
vi SCCSize; // 第i个连通分量的大小是SCCSize[i]，从0开始编号

/// SCC主函数
void Tarjan(){
    auto vn = g.size() - 1;

    Dfn.assign(vn + 1, TimeStamp = SCCCnt = StackTop = 0);
    IsInStack.assign(vn + 1, false);
    SCCSize.assign(vn + 1, 0);

    Belong.assign(vn + 1, -1);
	Low.assign(vn + 1, 0);
	Stack.assign(vn + 1, 0);


    for(int i=1;i<=vn;++i)if(0 == Dfn[i])dfs(i);
    SCCSize.erase(SCCSize.begin()+SCCCnt, SCCSize.end());
    return;
}

void dfs(int u){
    Dfn[u] = Low[u] = ++ TimeStamp;
    IsInStack[Stack[StackTop++] = u] = true;

    int v;
    for(auto i : g[u]){
        const auto & e = edges[i];
        if(0 == Dfn[v = e.to]){
            dfs(v);
            if(Low[v] < Low[u]) Low[u] = Low[v];
        }else if(IsInStack[v] && Dfn[v] < Low[u]){
            Low[u] = Dfn[v];
        }
    }

    /// 找到一个SCC
    if(Dfn[u] == Low[u]){
        do{
            IsInStack[v = Stack[--StackTop]] = false;
            ++SCCSize[Belong[v] = SCCCnt];
        }while(u != v);
        ++SCCCnt;
    }
}

/// 求kdag，由参数返回,从0开始编号
void kdag(vector<vector<int>>&kdag)const{
    kdag.assign(SCCCnt, vi());
    for(const auto & e : edges){
        int a = Belong[e.from];
        int b = Belong[e.to];
        if(a != b){
            kdag[a].emplace_back(b);
        }
    }
    for(auto & vec : kdag){
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
    }
    return;
}

vi Stack;
vector<bool> IsInStack;
int StackTop; // 辅助栈

vi Dfn, Low;
int TimeStamp; // 辅助数组

};

int N, M;
SCCTarjan SCC;

int proc(){
    SCC.Tarjan();
    int ans = 0;
    for(auto i : SCC.SCCSize)if(i>1)++ans;
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    SCC.init(N, M);
    for(int i=0;i<M;++i){
        int a, b;
        cin >> a >> b;
        SCC.mkDiEdge(a, b);
    }
    cout << proc() << endl;
    return 0;
}