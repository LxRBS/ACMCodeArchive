//求二分图最大独立集的点的数量，二分图最大独立集=总点数-最大匹配
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 1010;
int const SIZE_OF_EDGES = 251000;

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

int L[SIZE_OF_VERTICES];//Li与第i个点匹配的点，注意这个点编号是全图的编号而不是二分图编号，特别是对B部分的点

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
	fill(L,L+n+1,0);
}

//单向边
inline void mkEdge(int a,int b){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int D[SIZE_OF_VERTICES];
int Q[SIZE_OF_VERTICES];//辅助队列
bool bfs(int na,int nb,int n){
    bool ret = false;
    fill(D,D+n+1,0);

    int head,tail = 0;
    for(int i=1;i<=na;++i) if ( !L[i] ) Q[tail++] = i;//入队

    int u,v;
    for(head=0;head<tail;++head){
        //对每一个点的每一条边
        for(int p=Vertex[u=Q[head]];p;p=Edge[p].next){
            if ( !D[v=Edge[p].to] ){
                D[v] = D[u] + 1;
                if ( !L[v] ) ret = true;
                else D[L[v]] = D[v] + 1, Q[tail++] = L[v];
            }
        }
    }
    return ret;
}

bool dfs(int u){
    int v;
    for(int p=Vertex[u];p;p=Edge[p].next){
        if ( D[v=Edge[p].to] == D[u] + 1 ){
            D[v] = 0;
            if ( !L[v] || dfs(L[v]) ){
                L[ L[v] = u ] = v;
                return true;
            }
        }
    }
    return false;
}

//na是A的数量，nb是B的数量，n是总数量
int HopcroftKarp(int na,int nb,int n){
    int ret = 0;
    while( bfs(na,nb,n) ){
        for(int i=1;i<=na;++i){
            if ( !L[i] && dfs(i) ) ++ret;
        }
    }
    return ret;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initGraph(N<<1);
    int a,b,c;
    for(int i=1;i<=N;++i){
        a = getUnsigned() + 1;
        c = getUnsigned();
        for(int j=0;j<c;++j){
            b = getUnsigned() + 1;
            mkEdge(a,b+N);
        }
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) printf("%d\n",N-HopcroftKarp(N,N,N<<1)/2);
    return 0;
}
