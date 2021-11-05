/*
    在一个二维平面上，若干个格子有垃圾
    机器人只能从左上走到右下，向右、向下走
    问最少要多少个机器人才能捡光垃圾
    路径覆盖问题
    对每一对垃圾a/b，只要b在a的右下，则a到b有条边
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 25*25;
int const SIZE_OF_EDGES = SIZE_OF_VERTICES*SIZE_OF_VERTICES;
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
int X[700],Y[700];
int N;
bool read(){
    N = 1;
    scanf("%d%d",X+1,Y+1);
    if ( -1 == X[1] && -1 == Y[1] ) return false;

    initGraph(24*24);
    while(1){
        ++N;
        scanf("%d%d",X+N,Y+N);
        if ( 0 == X[N] && 0 == Y[N] ) break;

        for(int i=1;i<N;++i){
            if ( X[i] <= X[N] && Y[i] <= Y[N] ) mkEdge(i,N);
        }
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        --N;
        printf("%d\n",N-HopcroftKarp(N,N));
    }
    return 0;
}
