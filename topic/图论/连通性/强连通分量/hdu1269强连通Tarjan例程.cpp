/*
    给定有向图，判断是否只有一个SCC
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 10010;
int const SIZE_OF_EDGES = 300010;

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


inline void mkEdge(int a,int b,weight_t w=weight_t()){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int Stack[SIZE_OF_VERTICES], StackTop;//辅助栈
bool IsInStack[SIZE_OF_VERTICES];

int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];

int SCCCnt;//连通分量的总数量
int Belong[SIZE_OF_VERTICES];//第i个顶点属于第Belong[i]个强连通分量
int SCCSize[SIZE_OF_VERTICES];//第i个连通分量的大小

void dfs(int u){
    Dfn[u] = Low[u] = ++TimeStamp;

    //入栈
    IsInStack[ Stack[StackTop++] = u ] = true;

    //对u的每一条边
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];
        }else if ( IsInStack[v] && Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //找到一个SCC
    if ( Dfn[u] == Low[u] ){
        do{
            IsInStack[ v = Stack[--StackTop] ] = false;
            ++SCCSize[ Belong[v] = SCCCnt ];
        }while( v != u );

        ++SCCCnt;
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(IsInStack,IsInStack+vn+1,false);
    fill(SCCSize,SCCSize+vn+1,0);

    TimeStamp = SCCCnt = StackTop = 0;

    for(int i=1;i<=vn;++i){
        if ( 0 == Dfn[i] ){
            dfs(i);
        }
    }
}

int N,M;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    if ( 0 == N && 0 == M ) return false;

    initGraph(N);

    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
    }
    return true;

}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        Tarjan(N);
        printf(1==SCCCnt?"Yes\n":"No\n");
    }
    return 0;
}
