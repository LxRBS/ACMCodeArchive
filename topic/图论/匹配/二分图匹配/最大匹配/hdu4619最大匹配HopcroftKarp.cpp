/*
    若干个多米诺，横竖放置
    横着的与竖着的可能相交
    现在要求移除最少的多米诺，使得剩下的最多且各不相交，问最多剩下多少。
    典型的黑白格模型
    答案为最大匹配
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_VERTICES = 5010;
int const SIZE_OF_EDGES = 10000;
int const INF = 0x3F3F3F3F;

struct edge_t{
	int from,to;
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

//单向边
inline void mkEdge(int a,int b){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A部分的距离，B部分的距离
int _Q[SIZE_OF_VERTICES];//辅助队列
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = _Q, *tail = _Q;
    for(int i=1;i<=na;++i) if ( !LinkA[i] ) *tail++ = i;//入队

    _Dis = INF;
    int u,v;
    while( head < tail ){
        if ( DA[u = *head++] > _Dis ) continue;

        for(int p=Vertex[u];p;p=Edge[p].next){
            if ( 0 == DB[ v = Edge[p].to ] ){
                DB[v] = DA[u] + 1;
                if ( LinkB[v] ) DA[ *tail++ = LinkB[v] ] = DB[v] + 1;
                else _Dis = DB[v];
            }
        }
    }
    return _Dis < INF;
}

bool _Flag[SIZE_OF_VERTICES];//辅助标记数组
bool dfs(int u){
    int v;
    for(int p=Vertex[u];p;p=Edge[p].next){
        if ( !_Flag[v=Edge[p].to] && DB[v] == DA[u] + 1 ){
            _Flag[v] = true;
            if ( !LinkB[v] || ( DB[v] != _Dis && dfs(LinkB[v]) ) ){
                LinkA[ LinkB[v] = u ] = v;
                return true;
            }
        }
    }
    return false;
}

//na是A的数量，nb是B的数量
int HopcroftKarp(int na,int nb){
	fill(LinkA,LinkA+na+1,0);
	fill(LinkB,LinkB+nb+1,0);

    int ret = 0;
    while( bfs(na,nb) ){
        fill(_Flag,_Flag+nb+1,false);
        for(int i=1;i<=na;++i){
            if ( !LinkA[i] ) ret += dfs(i);
        }
    }
    return ret;
}

int N,M;
int NA,NB;
int Q[110][110];
bool read(){
    scanf("%d%d",&N,&M);
    if ( 0 == N && 0 == M ) return false;

    initGraph(5000);
    memset(Q,0,sizeof(Q));
    NA = NB = 0;
    int x,y;
    for(int i=0;i<N;++i){
        scanf("%d%d",&x,&y);
        if ( ( x + y ) & 1 ){
            if ( !Q[x][y] ) Q[x][y] = ++NA;
            if ( !Q[x+1][y] ) Q[x+1][y] = ++NB;
            mkEdge(Q[x][y],Q[x+1][y]);
        }else{
            if ( !Q[x][y] ) Q[x][y] = ++NB;
            if ( !Q[x+1][y] ) Q[x+1][y] = ++NA;
            mkEdge(Q[x+1][y],Q[x][y]);
        }
    }
    for(int i=0;i<M;++i){
        scanf("%d%d",&x,&y);
        if ( ( x + y ) & 1 ){
            if ( !Q[x][y] ) Q[x][y] = ++NA;
            if ( !Q[x][y+1] ) Q[x][y+1] = ++NB;
            mkEdge(Q[x][y],Q[x][y+1]);
        }else{
            if ( !Q[x][y] ) Q[x][y] = ++NB;
            if ( !Q[x][y+1] ) Q[x][y+1] = ++NA;
            mkEdge(Q[x][y+1],Q[x][y]);
        }
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        printf("%d\n",HopcroftKarp(NA,NB));
    }
    return 0;
}
