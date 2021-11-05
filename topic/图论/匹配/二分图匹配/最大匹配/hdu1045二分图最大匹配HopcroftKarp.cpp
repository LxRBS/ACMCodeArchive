/*
    给定棋盘，棋盘上有若干障碍物
    问最多能放多少个车使得互相不攻击
    如果没有障碍物，就是一个最小点覆盖，等于最大匹配
    行作为一部，每一行为相当于二分图的一个点，列作为一部
    现在有障碍物，则每一行可能需要分成二分图上的几个点
*/
#include <stdio.h>
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

int N,AN,BN,VN;
char A[10][10];

int BelongRow[10][10],BelongCol[10][10];
bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;

    fgets(A[0],9,stdin);
    for(int i=0;i<N;++i) fgets(A[i],9,stdin);

    //计算出所有行的部分
    int k = 1;
    for(int i=0;i<N;++i){
        int col = 0;
        while( col < N ){
            while( col < N && A[i][col] != '.' ) ++col;
            if ( N == col ) break;

            while( col < N && A[i][col] == '.' ) BelongRow[i][col++] = k;
            ++k;
        }
    }
    AN = k;

    //计算所有列的部分
    for(int i=0;i<N;++i){
        int row = 0;
        while( row < N ){
            while( row < N && A[row][i] != '.' ) ++row;
            if ( N == row ) break;

            while( row < N && A[row][i] == '.' ) BelongCol[row++][i] = k;
            ++k;
        }
    }
    BN = k - AN;

    //建图
    initGraph(VN=k);
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if('.'==A[i][j]){
        mkEdge(BelongRow[i][j],BelongCol[i][j]);
    }

    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        printf("%d\n",HopcroftKarp(AN,BN,VN));
    }
    return 0;
}
