#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct ufs_t{
    enum {SIZE=400010};
    int father[SIZE];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return x==father[x]?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(x)]=find(y);}
};

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 400010;
int const SIZE_OF_EDGES = 400010;

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
	ECnt = 1;
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

int N,M,K;
int A[SIZE_OF_VERTICES];
bool F[SIZE_OF_VERTICES] = {false};

void read(){
    scanf("%d%d",&N,&M);

    initGraph(N);
    for(int i=0;i<M;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        mkEdge(++x,++y);
    }

    scanf("%d",&K);
    for(int i=0;i<K;++i){
        scanf("%d",A+i);
        F[++A[i]] = true;
    }
}

int Ans[SIZE_OF_VERTICES] = {0};
ufs_t UF;
void proc(){
    UF.init(N);

    for(int i=1;i<=N;++i){
        if ( F[i] ) continue;

        for(int next=Vertex[i];next;next=Edge[next].next){
            int v = Edge[next].to;
            if ( F[v] ) continue;
            UF.unite(i,v);
        }
    }

    Ans[K] = 0;
    for(int i=1;i<=N;++i)if(!F[i]&&UF.find(i)==i)++Ans[K];

    for(int i=K-1;i>=0;--i){
        Ans[i] = Ans[i+1] + 1;

        int& u = A[i];
        F[u] = false;

        for(int next=Vertex[u];next;next=Edge[next].next){
            int v = Edge[next].to;
            if ( F[v] ) continue;

            if ( UF.find(u) != UF.find(v) ){
                UF.unite(u,v);
                --Ans[i];
            }
        }
    }

    for(int i=0;i<=K;++i)printf("%d\n",Ans[i]);
}
int main(){
    //freopen("1.txt","r",stdin);
    read();
    proc();
    return 0;
}

