namespace DAISHU{

struct TwoSat{ // 可满足性问题

using vi = vector<int>;
using vvi = vector<vi>;

int n;
vvi g;
vector<bool> result;

TwoSat() = default;
TwoSat(int nn):n(nn),g(nn+nn+1, vi()){}
void init(int nn){g.assign((n=nn)+nn+1, vi());}

/// 添加一个约束, a从1开始编号
/// 限定 a = zj
void addSingle(int a, int zj){
	if(zj) g[a+n].emplace_back(a);
	else g[a].emplace_back(a+n);
}

/// 限定 a&b = zj
void addAnd(int a, int b, int zj){
    if(zj) g[a+n].emplace_back(a), g[b+n].emplace_back(b);
	else g[a].emplace_back(b+n), g[b].emplace_back(a+n);
}

void addOr(int a, int b, int zj){
	if(zj) g[a+n].emplace_back(b), g[b+n].emplace_back(a);
	else g[a].emplace_back(a+n), g[b].emplace_back(b+n);
}

void addXor(int a, int b, int zj){
	if(zj) g[a+n].emplace_back(b), g[a].emplace_back(b+n), g[b+n].emplace_back(a), g[b].emplace_back(a+n);
	else g[a+n].emplace_back(b+n), g[a].emplace_back(b), g[b+n].emplace_back(a+n), g[b].emplace_back(a);
}

void addImply(int a, int az, int b, int bz){
    g[a+(az?0:n)].emplace_back(b+(bz?0:n));
}

/// 规范表达 a取az或者b取bz
void addReg(int a, int az, int b, int bz){
	int st = (az << 1) | bz;
	if(st == 3) addOr(a, b, 1);
	else if(st == 2) addImply(a, 0, b, 0), addImply(b, 1, a, 1);
	else if(st == 1) addImply(a, 1, b, 1), addImply(b, 0, a, 0);
	else addImply(a, 1, b, 0), addImply(b, 1, a, 0);
}

int SCCCnt; // 连通分量的总数
vi Belong;  // 第i个定点属于第Belong[i]个SCC
vi SCCSize; // 第i个连通分量的大小是SCCSize[i]，从0开始编号
vi Stack;
vector<bool> IsInStack;
int StackTop; // 辅助栈
vi Dfn, Low;
int TimeStamp; // 辅助数组

/// Trajan强连通分量
void scc(){
    auto vn = g.size() - 1;

    Dfn.assign(vn + 1, TimeStamp = SCCCnt = StackTop = 0);
    IsInStack.assign(vn + 1, false);
    SCCSize.assign(vn + 1, 0);

    Belong.assign(vn + 1, -1);
	Low.assign(vn + 1, 0);
	Stack.assign(vn + 1, 0);

	function<void(int)> __dfs = [&](int u){
		Dfn[u] = Low[u] = ++ TimeStamp;
		IsInStack[Stack[StackTop++] = u] = true;

		int v;
		for(auto v : g[u]){
			if(0 == Dfn[v]){
				__dfs(v);
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
	};


    for(int i=1;i<=vn;++i)if(0 == Dfn[i])__dfs(i);
    SCCSize.erase(SCCSize.begin()+SCCCnt, SCCSize.end());
    return;
}

/// SCC求解，O(N+M)
bool solveLinear(){
    scc();
	result.assign(n+1, 0);
	for(int zi,fi,i=1;i<=n;++i){
        if((zi = Belong[i]) == (fi = Belong[i+n])) return false;
        result[i] = zi < fi;
	}
	return true;
}

/// 深搜求字典序最小， O(NM)
bool solveSquare(){
    return true;
}

};


}
