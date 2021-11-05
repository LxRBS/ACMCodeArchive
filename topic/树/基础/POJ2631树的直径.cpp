/*
    求树的直径
    任选一点进行搜索，搜到最远点
    再从最远点进行搜索，又收到最远点
    两个最远点为树的直径，可以证明
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

int N,M;
bool read(){
    if ( 2 != scanf("%d%d",&N,&M) ) return false;

    initGraph(N);

    int a,b,w;
    char s[10];
    for(int i=0;i<M;++i){
        scanf("%d%d%d%s",&a,&b,&w,s);
        mkEdge(a,b,w);
    }
    return true;
}

int D[SIZE_OF_VERTICES];
int T;
void dfs(int u){
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next)if(-1==D[v=Edge[next].to]){
        D[v] = D[u] + Edge[next].weight;
        if ( D[T] < D[v] ) T = v;
        dfs(v);
    }
}

int main(){
    //freopen("1.txt","r",stdin);

    initGraph(10000);
    int a,b,w;
    while( 3 == scanf("%d%d%d",&a,&b,&w) ) mkEdge(a,b,w);

    fill(D,D+10001,-1);
    D[T=1] = 0;
    dfs(1);

    fill(D,D+10001,-1);
    D[T] = 0;
    dfs(T);

    printf("%d\n",D[T]);
    return 0;
}
