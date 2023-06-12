/*
    在有向图上找一条最长路
    以每一个入度为0的点做起点，记忆化搜索一遍。
*/

#include <stdio.h>
#include <string.h>
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
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,M;
int InDeg[SIZE_OF_VERTICES];

void read(){
    N = getUnsigned();
    M = getUnsigned();

    initGraph(N);
    fill(InDeg,InDeg+N+1,0);

    int a,b;
    for(int i=0;i<M;++i){
        a = getUnsigned();
        ++InDeg[b = getUnsigned()];
        mkEdge(a,b,getUnsigned());
    }
}

int D[SIZE_OF_VERTICES];
int Ans;

int dfs(int u){
    if (D[u]) return D[u];
    int tmp,ret = 0;
    for(int p=Vertex[u];p;p=Edge[p].next){
        if ( ret < (tmp=Edge[p].weight+dfs(Edge[p].to)) ){
            ret = tmp;
        }
    }

    return D[u] = ret;
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        read();

        fill(D,D+N+1,0);
        Ans = 0;
        for(int i=1;i<=N;++i)if(0==InDeg[i]){
            dfs(i);
            if ( Ans < D[i] ) Ans = D[i];
        }
        printf("%d\n",Ans);
    }
    return 0;
}
