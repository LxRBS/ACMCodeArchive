#include "graph.hpp"

namespace TULUN{

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

}