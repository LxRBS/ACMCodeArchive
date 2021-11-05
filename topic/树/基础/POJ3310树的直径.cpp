/*
    给定一个图，要求判断：
    无环
    存在一条路径，所有的点不在路径上就是路径上点的邻居

    首先这肯定要是一棵树，判断树使用连通无环来判断
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 40010;
int const SIZE_OF_EDGES = 80010;

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

//to build bi-directional edge
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

int D[SIZE_OF_VERTICES],Pre[SIZE_OF_VERTICES];
int S,T;
void dfs(int u){
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next)if(-1==D[v=Edge[next].to]){
        D[v] = D[u] + 1;
        Pre[v] = u;
        if ( D[T] < D[v] ) T = v;
        dfs(v);
    }
}

int N,E;
int Degree[SIZE_OF_VERTICES];
bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;

    initGraph(N);
    fill(Degree,Degree+N+1,0);
    scanf("%d",&E);

    int a,b;
    for(int i=0;i<E;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
        ++Degree[a];
        ++Degree[b];
    }
    return true;
}

struct ufs_t{
    enum{UF_SIZE=110};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

bool proc(){
    //判断是否为树
    UF.init(N);
    for(int i=2;i<ECnt;i+=2){
        if ( UF.find(Edge[i].from) == UF.find(Edge[i].to) ) return false;
        UF.unite(Edge[i].from,Edge[i].to);
    }

    //求树的直径
    fill(D,D+N+1,-1);
    D[T=1] = Pre[1] = 0;
    dfs(1);

    fill(D,D+N+1,-1);
    D[S=T] = Pre[T] = 0;
    dfs(S);

    int v;
    //T到S的路径为直径
    for(int i=T,j=Pre[T];j;i=j,j=Pre[j]){
        //检查非直径上的点的度数是否大于1
        for(int next=Vertex[j];next;next=Edge[next].next)if((v=Edge[next].to)!=Pre[j]&&v!=i){
            if ( Degree[v] > 1 ) return false;
        }
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);

    for(int kase=1;read();++kase){
        printf("Graph %d is ",kase);
        if ( N != E + 1 || !proc() ) printf("not ");
        printf("a caterpillar.\n");
    }

    return 0;
}
