/*
    给定图问是否有最小生成树，是否有次小生成树
    次小生成树可以同最小生成树
    有重边
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

struct ufs_t{
    enum {SIZE=110};
    int father[SIZE];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return x==father[x]?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(x)]=find(y);}
}UF;

//type of edge's weight
typedef int weight_t;
weight_t const INF = 1000000000;

//just as its names
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 500;

struct edge_t{
	int from,to;
	weight_t weight;
}Edge[SIZE_OF_EDGES];
int ECnt;

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 1;
}

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt++].weight = w;
}

bool operator < (edge_t const&lhs,edge_t const&rhs){
    return lhs.weight < rhs.weight || ( lhs.weight == rhs.weight && lhs.from < rhs.from )
        || ( lhs.weight == rhs.weight && lhs.from == rhs.from && lhs.to < rhs.to );
}

//Kruskal求最小生成树或者候选的次小生成树
//返回值为生成树的权值和，-1表示不连通
//vn:点的数量
//en:边的数量
//uf:辅助用的并查集
//mstEdges:最小生成树的边，求最小生成树时的输出参数，1base
//ban:表示生成生成树的时候禁用某条边，为0表示不禁用
weight_t Kruskal(int vn,int en,ufs_t&uf,int mstEdges[],int ban=0){
    if ( 0 == ban ) sort(Edge+1,Edge+en+1);
    uf.init(vn);

    weight_t ret = 0;
    int cnt = 1;

    for(int i=1;i<=en;++i)if(i!=ban){
        if ( uf.find(Edge[i].from) == uf.find(Edge[i].to) ) continue;

        ret += Edge[i].weight;
        uf.unite(Edge[i].from,Edge[i].to);
        if( 0 == ban ) mstEdges[cnt] = i;
        ++cnt;

        if ( vn == cnt ) break;
    }
    return vn == cnt ? ret : -1;
}

//求次小生成树，返回值为次小生成树的权值
//vn:点的数量
//en:边的数量
//uf:辅助用的并查集
//mstEdges:最小生成树的边，求最小生成树时的输出参数，1base
weight_t Kruskal42ndMST(int vn,int en,ufs_t&uf,int mstEdges[]){
    weight_t tmp, ret = INF;
    for(int i=1;i<vn;++i){
        tmp = Kruskal(vn,en,uf,mstEdges,mstEdges[i]);
        if ( -1 != tmp && tmp < ret ) ret = tmp;
    }
    return INF == ret ? -1 : ret;
}

int N,M;
int MstEdges[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int a,b,w,nofkase;
    scanf("%d",&nofkase);

    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d%d",&N,&M);

        initGraph(N);
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&a,&b,&w);
            mkEdge(a,b,w);
        }

        printf("Case #%d : ",kase);

        //求最小生成树
        weight_t mst = Kruskal(N,M,UF,MstEdges);

        if ( -1 == mst ){
            printf("No way\n");
            continue;
        }

        //求次小生成树
        weight_t mst2 = Kruskal42ndMST(N,M,UF,MstEdges);

        if ( -1 == mst2 ){
            printf("No second way\n");
        }else{
            printf("%d\n",mst2);
        }
    }
    return 0;
}

