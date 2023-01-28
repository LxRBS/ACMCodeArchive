#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_pbds;


namespace IO{

char *__abc147, *__xyz258, __ma369[1000000];
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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}

namespace TULUN{

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


}


namespace TULUN{

struct CutAndBridge{

const Graph & g;

int BridgeCnt;//桥的数量
vector<bool> IsCut;//点i是否为割点
vector<bool> IsBridge;//边i是否为桥
vector<int> AddBlocks;// ABi表示删除i点之后多出来的块数

CutAndBridge() = delete;
CutAndBridge(const Graph & gg):g(gg){
    auto vn = g.node_size();
	auto en = g.edges.size();

	Dfn.assign(vn + 1, TimeStamp = BridgeCnt = 0);	
	Low.assign(vn + 1, 0);
	
	AddBlocks.assign(vn + 1, 0);
	IsCut.assign(vn + 1, false);

	IsBridge.assign(en, false);
	IsVisited.assign(en, false);    

	for(int i=1;i<=vn;++i)if(0==Dfn[i])dfs(i, i);
	return;
}

void dfs(int u, int pre){
	Dfn[u] = Low[u] = ++TimeStamp;

	int v, son = 0;
	for(auto i : g[u]){
		IsVisited[i] = IsVisited[i ^ 1] = true;
		const auto & e = g.edges[i];
        if(0 == Dfn[v = get<1>(e)]){
            ++son;
			dfs(v, u);
			if(Low[v] < Low[u]) Low[u] = Low[v];

			/// 这个if是桥
			if(Dfn[u] < Low[v]){
				IsBridge[i] = IsBridge[i ^ 1] = true;
				++BridgeCnt;
			}

			/// 这个if是割点
			if(u != pre && Dfn[u] <= Low[v]){
				IsCut[u] = true;
				++AddBlocks[u];
			}
		}else if(Dfn[v] < Low[u]){
            Low[u] = Dfn[v];
		}
	}

	/// 符合割点的条件1
	if(u == pre && son > 1) IsCut[u] = true;
	if(u == pre) AddBlocks[u] = son - 1;
}


int TimeStamp;
vector<int> Dfn, Low;
vector<bool> IsVisited; //边的标记数组


};

}

TULUN::Graph G;
int N, M;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
	N = getInt(); M = getInt();
    G.init(N, M+M);
	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
		G.mkBiEdges(a, b, 0);
	}
	TULUN::CutAndBridge cut(G);
	int ans = accumulate(cut.IsCut.begin(), cut.IsCut.end(), 0);
	printf("%d\n", ans);
	for(int i=1;i<=N;++i)if(cut.IsCut[i])printf("%d ", i);printf("\n");
	return 0;
}