/*
    ³àÂãÂãµÄMST
*/

#include <stdio.h>
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
typedef int weight_t;

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

    return ret;
}

int N,M;
int L2I[256];

bool read(){
    scanf("%d",&N);
    if (0==N) return false;

    fill(L2I,L2I+256,0);

    initGraph(N);
    M=0;
    char s[5];
    int a,b,w;
    int m,k = 0;
    for(int i=1;i<N;++i){
        scanf("%s%d",s,&m);
        M += m;

        if ( 0 == L2I[*s] ) L2I[*s] = ++k;
        a = L2I[*s];

        for(int j=0;j<m;++j){
            scanf("%s%d",s,&w);

            if ( 0 == L2I[*s] ) L2I[*s] = ++k;
            b = L2I[*s];

            mkEdge(a,b,w);
        }
    }
    return true;
}

ufs_t UF;
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) printf("%d\n",Kruskal(N,M,UF));
    return 0;
}

