/**
 * 给定长度为N的数组A。一共进行N轮游戏。
 * 第i轮，Aoki先确定一个数，记作K；然后Taka再确定一个数记作S；
 * 然后进行K次操作，令x = Ax，初始时x=S。
 * 如果x最后变成了i，则Taka胜。问Taka一共能够赢多少轮
 * 整个其实构成一个内向基环树的森林，如果第i个点在环上，Taka必然能够获胜，只需根据K的大小选择合适的起点即可
 * 否则，Aoki只需选一个非常大的数即可。
 * 使用SCCTarjan算法判断一下即可。
 * 注意自环边特判一下。
 */
#include <bits/stdc++.h>
using namespace std;

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
    edges.clear();
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


struct SCCTarjan{

using vi = vector<int>;

const Graph & g;

int SCCCnt; // 连通分量的总数
vi Belong;  // 第i个定点属于第Belong[i]个SCC
vi SCCSize; // 第i个连通分量的大小是SCCSize[i]，从0开始编号

SCCTarjan() = delete;

/// 对graph做SCC，不改变graph的内容
SCCTarjan(const Graph & graph):g(graph){
    auto vn = g.node_size();

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
        const auto & e = g.edges[i];
        if(0 == Dfn[v = get<1>(e)]){
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

vi Stack;
vector<bool> IsInStack;
int StackTop; // 辅助栈

vi Dfn, Low;
int TimeStamp; // 辅助数组

};

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

int N;
vi A;
Graph G;

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    
    A.assign(N + 1, 0);
    G.init(N, N);

    int ans = 0;
    for(int i=1;i<=N;++i){
        cin >> A[i];
        G.mkOneEdge(i, A[i], 0);
        if(i == A[i]){
            A[i] = 0;
            ++ans;
        }
    }

    SCCTarjan scc(G);
    for(int i=1;i<=N;++i){
        if(0 == A[i]) continue;
        if(scc.SCCSize[scc.Belong[i]] > 1) ++ans;
    }
    cout << ans << endl;
    return 0;
}
