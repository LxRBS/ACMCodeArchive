/*
    距离不小于10m不大于1000m可以建路，100元每米
    问最小花费
*/

#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

struct ufs_t{
    enum {SIZE=100};
    int father[SIZE];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return x==father[x]?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(x)]=find(y);}
};

//type of edge's weight
typedef double weight_t;

//just as its names
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 10000;

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

//vn is the amount of vertieces, indexed from 1
//en is the amount of edges, indexed from 1
//uf is auxiliary union-find set
//returns the weight of MST
weight_t Kruskal(int vn,int en,ufs_t&uf){
    uf.init(vn);
    sort(Edge+1,Edge+en+1);

    weight_t ret = 0;
    int cnt = 1;

    for(int i=1;i<=en;++i){
        if ( uf.find(Edge[i].from) == uf.find(Edge[i].to) ) continue;

        ret = ret + Edge[i].weight;
        uf.unite(Edge[i].from,Edge[i].to);
        ++cnt;

        if ( vn == cnt ) break;
    }

    return vn == cnt ? ret : 0.0;
}

int N,M;
int X[110],Y[110];
bool read(){
    scanf("%d",&N);

    initGraph(N);
    for(int i=1;i<=N;++i)scanf("%d%d",X+i,Y+i);

    M = 0;
    for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j){
        int x = X[i] - X[j];
        int y = Y[i] - Y[j];
        int t = x * x + y * y;
        if ( 100 <= t && t <= 1000000 ) mkEdge(i,j,sqrt(t)), ++M;
    }

    return true;
}

ufs_t UF;
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        double r = Kruskal(N,M,UF);
        if ( 0 == r ) printf("oh!\n");
        else printf("%.1f\n",r*100.0);
    }
    return 0;
}

