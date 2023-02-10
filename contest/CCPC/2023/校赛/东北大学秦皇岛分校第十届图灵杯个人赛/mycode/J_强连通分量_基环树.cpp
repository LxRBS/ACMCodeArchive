/**
 * 给定一个有向图，每个点最多只有一条出边，有一个特殊节点，特殊节点本来无边
 * 本质上就是问给特殊节点加一条出边，如何做可以使得加边以后形成的新环节点数量最多。
 * 整个图其实是一个基环树森林，可以DP。这里本质上是一样的，做一个SCC缩点，然后在KDAG上查找最长的链即可。
 */
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
int const SIZE = 133;
#else
int const SIZE = 1E6+10;
#endif

struct SCCTarjan{

using vi = vector<int>;
using vvi = vector<vi>;

const vvi & g;

int SCCCnt; // 连通分量的总数
vi Belong;  // 第i个定点属于第Belong[i]个SCC
vi SCCSize; // 第i个连通分量的大小是SCCSize[i]，从0开始编号

SCCTarjan() = delete;

/// 对graph做SCC，不改变graph的内容
SCCTarjan(const vvi & graph):g(graph){
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

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

int N;
vvi G;
int LaoWang;
vi Deg;
vvi Kdag;
unique_ptr<SCCTarjan> pSCC = nullptr;

vi D;

int dfs(int u){
    // if(pSCC->SCCSize[u] > 1) return 0;
    if(Kdag[u].size() == 0) return 0;
    if(D[u] != -1) return D[u];

    assert(Kdag[u].size() == 1);
    D[u] = 1 + dfs(Kdag[u][0]);
    return D[u];
}
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    G.assign((LaoWang = (N = getInt()) + 1) + 1, vi());
    for(int a,i=1;i<=N;++i){
        a = getInt();
        G[i].emplace_back(a?a:LaoWang);
    }
    
    pSCC = make_unique<SCCTarjan>(SCCTarjan(G));
    const auto & scc = *pSCC;

    Kdag.assign(scc.SCCCnt, vi());
    Deg.assign(scc.SCCCnt, 0);
    for(int i=1;i<=N;++i){
        assert(1 == G[i].size());
        int a = i, b = G[i][0];
        auto ba = scc.Belong[a], bb = scc.Belong[b];
        if(ba != bb){
            Kdag[ba].emplace_back(bb);
            ++Deg[bb];
        }
    }

    D.assign(scc.SCCCnt, -1);
    for(int i=0;i<scc.SCCCnt;++i){
        if(0 == Deg[i]){
            dfs(i);
        }
    }

    int total = max(0, *max_element(D.begin(), D.end()));
    for(int i=0;i<scc.SCCCnt;++i){
        if(0 == Kdag[i].size()){
            total += scc.SCCSize[i];
        }
    }

    cout << total << endl;
    return 0;
}