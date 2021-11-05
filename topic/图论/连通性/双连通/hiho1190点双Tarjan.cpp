//无向图，求出点双连通分量，可以处理重边，虽然此题没有重边
#include <stdio.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 20010;
int const SIZE_OF_EDGES = 200110;

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
inline void mkEdge(int a,int b,weight_t w=weight_t()){
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

int Stack[SIZE_OF_EDGES],StackTop;//辅助栈，基于边的
int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
int Belong2BiCC[SIZE_OF_EDGES];//边i属于第Bi个双连通分量，从1开始；对点来说，割点可能同时属于多个点双连通
int Represent[SIZE_OF_EDGES];//Ri表示第i个双连通中边数编号最小的边
bool IsVisited[SIZE_OF_EDGES];//边的标记数组，有重边时需用此数组
int BiCCCnt;//双连通分量的数量

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    int v, edge = 0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( !IsVisited[next] ){
        IsVisited[next] = IsVisited[next^1] = true;

        if ( 0 == Dfn[v=Edge[next].to] ){
            //入栈
            Stack[StackTop++] = next;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            //说明u是割点，栈内的边都属于同一个点双连通
            if ( Dfn[u] <= Low[v] ){
                Represent[Belong2BiCC[next] = Belong2BiCC[next^1] = ++BiCCCnt] = next;
                while( ( edge = Stack[--StackTop] ) != next ){
                    Belong2BiCC[edge] = Belong2BiCC[edge^1] = BiCCCnt;
                    //edge是程序内部的编号，题目中边的编号应该是edge/2，正向边反向边都是这个式子
                    if ( edge < Represent[BiCCCnt] ) Represent[BiCCCnt] = edge;
                }
            }
        }else if ( Dfn[v] < Dfn[u] ){
            Low[u] = min(Low[u],Dfn[v]);
            Stack[StackTop++] = next;
        }
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(Belong2BiCC,Belong2BiCC+ECnt,0);
    fill(IsVisited,IsVisited+ECnt,false);
    TimeStamp = BiCCCnt = StackTop = 0;
    for(int i=1;i<=vn;++i)if ( 0 == Dfn[i] )dfs(i,i);
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();

    initGraph(n);
    for(int i=0;i<m;++i){
        mkEdge(getUnsigned(),getUnsigned());//反正是双向边
    }

    Tarjan(n);
    printf("%d\n%d",BiCCCnt,Represent[Belong2BiCC[2]]>>1);
    for(int i=4;i<ECnt;i+=2)printf(" %d",Represent[Belong2BiCC[i]]>>1);
    printf("\n");
    return 0;
}
