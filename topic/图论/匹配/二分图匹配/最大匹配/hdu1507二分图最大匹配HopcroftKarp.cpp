/*
    一个矩形区域分成若干格
    池塘不能出售，剩下的格子必须按1×2或者2×1出售
    问最多能卖多少块，并且输出任一方案
    典型的黑白格，最大匹配
*/
#include <stdio.h>
#include <string.h>
#include <vector> 
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 10010;
int const SIZE_OF_EDGES = 40010;
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

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int N,M,K;
int NA,NB;
bool F[110][110];
int A[110][110];
vector<pair<int,int> > VA,VB;
bool read(){
    N = getUnsigned(), M = getUnsigned();
    if ( 0 == N && 0 == M ) return false;

    K = getUnsigned();
    memset(F,0,sizeof(F));
    int a,b;
    for(int i=0;i<K;++i){
        a = getUnsigned();
        b = getUnsigned();
        F[a][b] = true;
    }

    memset(A,0,sizeof(A));
    initGraph(N*M-K);
    NA = NB = 0;
    VA.assign(1,make_pair(0,0));
    VB.assign(1,make_pair(0,0));
    for(int i=1;i<=N;++i)for(int j=1;j<=M;++j)if(((i+j)&1)&&!F[i][j]){
        A[i][j] = ++NA;
        VA.push_back(make_pair(i,j));
        for(int d=0;d<4;++d){
            int dr = i + DR[d];
            int dc = j + DC[d];
            if ( 1 <= dr && dr <= N && 1 <= dc && dc <= M && !F[dr][dc] ){
                if ( 0 == A[dr][dc] ) {A[dr][dc] = ++NB;VB.push_back(make_pair(dr,dc));}
                mkEdge(A[i][j],A[dr][dc]);
            }
        }
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        printf("%d\n",HopcroftKarp(NA,NB));
        for(int i=1;i<=NA;++i)if(LinkA[i]){
            printf("(%d,%d)--(%d,%d)\n",VA[i].first,VA[i].second,VB[LinkA[i]].first,VB[LinkA[i]].second);
        }
        printf("\n");
    }
    return 0;
}
