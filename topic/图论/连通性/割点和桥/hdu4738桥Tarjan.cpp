//无向连通图，求权值最小的桥，如果图本来就是不连通的，输出0
#include <stdio.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 1010;
int const SIZE_OF_EDGES = 2000110;

struct edge_t{
	int from,to;
	weight_t weight;
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
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int TimeStamp;
int Dfn[SIZE_OF_VERTICES],Low[SIZE_OF_VERTICES];
//int AddBlocks[SIZE_OF_VERTICES];//ABi表示删除i点之后多出来的块数
bool IsBridge[SIZE_OF_EDGES];//边i是否为桥
//bool IsCut[SIZE_OF_VERTICES];//点i是否为割点
bool IsVisited[SIZE_OF_EDGES];//边的标记数组，有重边时有用
int BridgeCnt;//桥的数量
int Ans;

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    int v,son = 0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( !IsVisited[next] ){
        IsVisited[next] = IsVisited[next^1] = true;

        if ( 0 == Dfn[v=Edge[next].to] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            //*
            //桥
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
                ++BridgeCnt;
                //记录答案
                if ( 0 == Ans || Edge[next].weight <= Edge[Ans].weight ) Ans = next;
            }
            //*/

            /*
            //符合割点的条件2
            if ( u != pre && Dfn[u] <= Low[v] ){
                IsCut[u] = true;
                ++AddBlocks[u];
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //符合割点的条件1
    //if ( u == pre && son > 1 ) IsCut[u] = true;
    //if ( u == pre ) AddBlocks[u] = son - 1;
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    //fill(AddBlocks,AddBlocks+vn+1,0);
    //fill(IsCut,IsCut+vn+1,false);
    fill(IsBridge,IsBridge+ECnt,false);
    fill(IsVisited,IsVisited+ECnt,false);
    TimeStamp = BridgeCnt = 0;

    for(int i=1;i<=vn;++i)if(0==Dfn[i])dfs(i,i);
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

struct ufs_t{
    enum{UF_SIZE=1010};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int N,M;
bool read(){
    N = getUnsigned();
    M = getUnsigned();
    if ( 0 == N && 0 == M ) return false;

    initGraph(N);
    UF.init(N);
    int a,b;
    for(int i=0;i<M;++i){
        a = getUnsigned();
        b = getUnsigned();
        mkEdge(a,b,getUnsigned());
        UF.unite(a,b);
    }
    return true;
}

int proc(){
    //判整图的连通性
    for(int i=2;i<=N;++i)if(UF.find(1)!=UF.find(i))return 0;

    Ans = 0;
    Tarjan(N);

    //没有桥，实际上就是只有一个双连通
    if ( 0 == BridgeCnt ) return -1;

    int w = Edge[Ans].weight;
    return w ? w : 1;
}
int main(){
    //freopen("1.txt","r",stdin);
    while ( read() ) printf("%d\n",proc());
    return 0;
}
