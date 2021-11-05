/*
    给定无向带权图，问MST是否唯一
    算一下次小生成树
*/
#include <cstdio>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct ufs_t{
    enum {SIZE=110};
    int father[SIZE];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return x==father[x]?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(x)]=find(y);}
};

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 20010;

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

int MSTEdge[SIZE_OF_EDGES];

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

        MSTEdge[cnt] = i;
        ret = ret + Edge[i].weight;
        uf.unite(Edge[i].from,Edge[i].to);
        ++cnt;

        if ( vn == cnt ) break;
    }

    return ret;
}

int N,M;
void read(){
    scanf("%d%d",&N,&M);

    initGraph(N);
    for(int i=0;i<M;++i){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        mkEdge(a,b,c);
    }
}

ufs_t UF;

//计算一下次小生成树
weight_t secondMST(int vn,int en,int mst[],weight_t mstWeight,ufs_t&uf){
    int ans = 2000000000;
    for(int i=1;i<vn;++i){//删除该边，再求一个MST
        uf.init(vn);

        weight_t ret = 0;
        int cnt = 1;

        for(int j=1;j<=en;++j)if(j!=mst[i]){
            if ( uf.find(Edge[j].from) == uf.find(Edge[j].to) ) continue;

            uf.unite(Edge[j].from,Edge[j].to);
            ret += Edge[j].weight;
            ++cnt;

            if ( vn == cnt ) break;
        }

        if ( vn == cnt ){
            if ( ret == mstWeight ) return mstWeight;
            if ( ret < ans ) ret = ans;
        }
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        int w = Kruskal(N,M,UF);
        int w2 = secondMST(N,M,MSTEdge,w,UF);
        if ( w == w2 ) printf("Not Unique!\n");
        else printf("%d\n",w);
    }

    return 0;
}

