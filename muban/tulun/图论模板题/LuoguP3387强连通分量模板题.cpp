#include <bits/stdc++.h>
using namespace std;

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

}


int N, M;
TULUN::Graph G;
vector<int> W;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    W.assign(N + 1, 0);
    for(int i=1;i<=N;++i) cin >> W[i];
    G.init(N, M);
	for(int a,b,i=0;i<M;++i){
        cin >> a >> b;
        G.mkOneEdge(a, b, 0);
    }

    TULUN::SCCTarjan scc(G);
	
	/// 首先把SCC的权值计算出来
	vector<int> w(scc.SCCCnt, 0);
	for(int i=1;i<=N;++i) w[scc.Belong[i]] += W[i];

    /// 制作kdag，从0开始编号
    vector<vector<int>> kdag(scc.SCCCnt, vector<int>());
	vector<int> deg(scc.SCCCnt, 0);
    for(const auto & e : G.edges){
		int a = scc.Belong[get<0>(e)];
		int b = scc.Belong[get<1>(e)];
        if(a != b){
			kdag[a].emplace_back(b);
			++deg[b];
		}
	} 

	/// 有向无环图上做个dp
	vector<int> d(scc.SCCCnt, 0);
	queue<int> q;
	for(int i=0;i<scc.SCCCnt;++i)if(0==deg[i]){
		d[i] = w[i]; q.push(i); 
	}
    
    while(!q.empty()){
		auto h = q.front(); q.pop();
		for(int v : kdag[h]){
			d[v] = max(d[h], d[v]);
            if(0 == --deg[v]) {
				q.push(v);
				d[v] += w[v];
			}
		}
	}

	auto ans = *max_element(d.begin(), d.end());
	cout << ans << endl;
    return 0;
}