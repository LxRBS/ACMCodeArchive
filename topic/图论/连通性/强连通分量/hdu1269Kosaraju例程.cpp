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
int Vertex[2][SIZE_OF_VERTICES];//0表示正向图，1表示反向图

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex[0],Vertex[0]+n+1,0);
	fill(Vertex[1],Vertex[1]+n+1,0);
}

//正向图建边，反向图建边
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[0][a];
	Vertex[0][a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[1][b];
	Vertex[1][b] = ECnt ++;
}

//原图的后序遍历
int PostOrder[SIZE_OF_VERTICES];
bool SCCFlag[SIZE_OF_VERTICES];
int PostCnt;

void dfs1(int u){
    SCCFlag[u] = true;
    for(int next=Vertex[0][u];next;next=Edge[next].next){
        if ( !SCCFlag[Edge[next].to] ){
            dfs1(Edge[next].to);
        }
    }
    PostOrder[PostCnt++] = u;
}

//反向图上的遍历
int Belong[SIZE_OF_VERTICES];//Belong[i]表示顶点i属于第Belong[i]个SCC
int SCCSize[SIZE_OF_VERTICES];//第i个强连通分量的大小

//参数2为强连通分量的编号
void dfs2(int u,int sccidx){
    SCCFlag[u] = true;
    ++SCCSize[Belong[u] = sccidx];
    for(int next=Vertex[1][u];next;next=Edge[next].next){
        if ( !SCCFlag[Edge[next].to] ){
            dfs2(Edge[next].to,sccidx);
        }
    }
}

//输入点的数量，输出强连通分量的数量
int Kosaraju(int vn){
    PostCnt = 0;
    fill(SCCFlag,SCCFlag+vn+1,false);
    for(int i=1;i<=vn;++i){
        if ( !SCCFlag[i] ){
            dfs1(i);
        }
    }

    int sccidx = 0;
    fill(SCCFlag,SCCFlag+vn+1,false);
    fill(SCCSize,SCCSize+vn+1,0);
    for(int i=PostCnt-1;i>=0;--i){
        if ( !SCCFlag[PostOrder[i]] ){
            dfs2(PostOrder[i],sccidx++);
        }
    }

    return sccidx;
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
        int r = Kosaraju(N);
        printf(1==r?"Yes\n":"No\n");
    }
    return 0;
}
