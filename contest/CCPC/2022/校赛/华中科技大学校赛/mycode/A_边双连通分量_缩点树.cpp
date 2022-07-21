/**
 * 无向连通图，若干个询问。每次问：给定uvxy4个点，问任选ux和vy或者uy和vx的路径的公共边最少是多少
 * 考虑边双，如果4个点在同一个边双中，则必然公共边为0，因为没有一条边是必须同时存在于两条路径之中的
 * 边双缩点后必然形成一棵树，于是题目变为了树上给定4个点，问路径的公共边数量。 
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100001];
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
int const SIZE = 2E5+7;
#endif

//just as its names
int const SIZE_OF_VERTICES = SIZE;
int const SIZE_OF_EDGES = SIZE * 3;

struct edge_t{
	int from,to;
	//weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

//双向边
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int Stack[SIZE_OF_VERTICES],StackTop;//辅助栈
int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
//bool IsBridge[SIZE_OF_EDGES];//边i是否为桥
bool IsVisited[SIZE_OF_EDGES];//边的标记数组，有重边时需用此数组进行判断
int Belong2BiCC[SIZE_OF_VERTICES];//点i属于第Bi个双连通分量，从1开始
int Represent[SIZE_OF_VERTICES];//Ri表示第i个边双的代表，也就是编号最小的那个点
int BiCCCnt;//双连通分量的数量

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    //入栈
    Stack[StackTop++] = u;

    //对u的每一条边
    int v,son=0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( !IsVisited[next] ){
        IsVisited[next] = IsVisited[next^1] = true;

        if ( 0 == Dfn[v=Edge[next].to] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            /*//桥
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    if ( Low[u] == Dfn[u] ){//u和其上的点在同一个分量中
        Represent[Belong2BiCC[u] = ++BiCCCnt] = u;
        do{
            Belong2BiCC[v=Stack[--StackTop]] = BiCCCnt;
            if ( v < Represent[BiCCCnt] ) Represent[BiCCCnt] = v;
        }while( v != u );
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(Belong2BiCC,Belong2BiCC+vn+1,0);
    fill(IsVisited,IsVisited+ECnt,false);
    //fill(IsBridge,IsBridge+ECnt,false);
    BiCCCnt = StackTop = 0;

    TimeStamp = 0;

    for(int i=1;i<=vn;++i)if ( 0 == Dfn[i] )dfs(i,i);
}

struct ufs_t{
    enum{UF_SIZE=SIZE};
    int father[UF_SIZE+1];
    
    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

using vi = vector<int>;
int N, M, Q;
vi G[SIZE];

struct problem_t{
	int u,v,x,y;
}Problem[SIZE];

using map_t = unordered_map<int, int>;
map_t LCAData[SIZE];
bool Flag[SIZE];
int Depth[SIZE];

void LCA(){
	UF.init(BiCCCnt);    
	
	function<void (int, int)> _dfs = [&](int u, int p)->void{
		Depth[u] = Depth[p] + 1;
        Flag[UF.father[u] = u] = true;
		for(auto son: G[u]){
            if(son == p) continue;
			_dfs(son, u);
			UF.father[son] = u;
		}

		for(auto & p: LCAData[u]){
			if(!Flag[p.first]) continue;
			
			p.second = UF.find(p.first);
			LCAData[p.first][u] = p.second;
		}
	};

	_dfs(1, 0);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    initGraph(N = getInt()); M = getInt();
	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
		mkEdge(a, b);
	}

	Tarjan(N); // 边双
	/// 建树，对所有的边
	UF.init(BiCCCnt);
    for(int a,b,i=2;i<ECnt;i+=2){
        a = Edge[i].from; b = Edge[i].to;
		if((a=Belong2BiCC[a]) == (b=Belong2BiCC[b])) continue;
		/// 从a块到b块已经建过边
		if(UF.find(a) == UF.find(b)) continue;
	    /// 从a到b建边
		G[a].push_back(b); G[b].push_back(a);
		UF.unite(a, b);
	}
	/// 输入问题
	Q = getInt();
	for(int u,v,x,y,q=1;q<=Q;++q){
        Problem[q].u = u = Belong2BiCC[getInt()];
		Problem[q].v = v = Belong2BiCC[getInt()];
		Problem[q].x = x = Belong2BiCC[getInt()];
		Problem[q].y = y = Belong2BiCC[getInt()];
		/// 需要求取多对LCA
        if(u != x){
			LCAData[u].insert({x, 0});
			LCAData[x].insert({u, 0});
		}
		if(u != y){
			LCAData[u].insert({y, 0});
			LCAData[y].insert({u, 0});
		}
        if(v != x){
			LCAData[v].insert({x, 0});
			LCAData[x].insert({v, 0});
		}
		if(v != y){
			LCAData[v].insert({y, 0});
			LCAData[y].insert({v, 0});
		}	
		if(u != v){
			LCAData[u].insert({v, 0});
			LCAData[v].insert({u, 0});
		}	
		if(x != y){
			LCAData[x].insert({y, 0});
			LCAData[y].insert({x, 0});
		}
	}

	/// 求一个LCA
	LCA();

	auto dist = [](int a, int b)->int{
		if(a == b) return 0;
        auto it = LCAData[a].find(b);
		assert(it != LCAData[a].end());
		return Depth[a] - Depth[it->second] + Depth[b] - Depth[it->second];
	};

	/// 答问题
	for(int u,v,x,y,q=1;q<=Q;++q){
        u = Problem[q].u;  v = Problem[q].v; 
		x = Problem[q].x;  y = Problem[q].y;
        /// uv的lca
		int uv = dist(u, v), xy = dist(x, y);
		int ux = dist(u, x), vy = dist(v, y);
		int uy = dist(u, y), vx = dist(v, x);
		int ans = min(ux + vy, uy + vx);
		ans -= uv + xy;
		if(ans < 0) ans = 0;
		printf("%d\n", ans>>1);
	}
    return 0;
}