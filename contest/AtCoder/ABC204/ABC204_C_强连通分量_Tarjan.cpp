/**
 * 给定有向图，问有多少点对(u, v)满足u可到v
 * 求一个SCC，然后在KDAG上对每一个点跑一个BFS
 * 不过看起来SCC并无必要。
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
int const SZ = 34;
#else
int const SZ = 2E5+10;
#endif

struct SCCTarjan{

using vi = vector<int>;
using Graph = vector<vi>;

const Graph & g;

int SCCCnt; // 连通分量的总数
vi Belong;  // 第i个定点属于第Belong[i]个SCC
vi SCCSize; // 第i个连通分量的大小是SCCSize[i]，从0开始编号

SCCTarjan() = delete;

/// 对graph做SCC，不改变graph的内容
SCCTarjan(const Graph & graph):g(graph){
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
        if(0 == Dfn[v = i]){
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

int N, M;
vvi G;

int proc(int u, const vvi & g, const SCCTarjan & scc){
    queue<int> q;
    q.push(u);
    vi flag(g.size(), 0);
    flag[u] = 1;
    int tmp = 0;
    while(not q.empty()){
        auto h = q.front(); q.pop();
        for(int v : g[h]){
            if(flag[v]) continue;
            flag[v] = 1;
            q.push(v);
            tmp += scc.SCCSize[v];
        }
    }
    int sz = scc.SCCSize[u];
    return sz * sz + sz * tmp;
}

int proc(){
    SCCTarjan scc(G);
    int n = scc.SCCCnt;
    vvi kdag(n, vi());
    for(int i=1;i<=N;++i){
        int a = scc.Belong[i];
        for(int j : G[i]){
            int b = scc.Belong[j];
            if(a != b){
                kdag[a].push_back(b);
            }
        }
    }

    int ans = 0;
    for(int i=0;i<n;++i){
        ans += proc(i, kdag, scc);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    G.assign(N + 1, vi());
    for(int a,b,i=0;i<M;++i){
        cin >> a >> b;
        G[a].push_back(b);
    }
    cout << proc() << endl;
    return 0;
}