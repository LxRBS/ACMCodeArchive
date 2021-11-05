/*
    给定一个棋盘，问最多能放多少个车
    而且问关键点有多少个
    这个题目与hdu1045一样，应该缩点
    但实际上直接按行列建边即可
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 505;

bool Graph[SIZE][SIZE];//二分图矩阵
int L[SIZE];//Li为A中与Bi匹配的点
bool Flag[SIZE];//Fi表示Bi是否已在增广路中，在一次搜索中

inline void initGraph(int na,int nb){
    memset(Graph,0,sizeof(Graph));
}

//node为A中的节点编号，从1开始
int dfs(int node,int nb){
    for(int i=1;i<=nb;++i){
        //如果没有边，或者已经在增广路上
        if ( !Graph[node][i] || Flag[i] ) continue;
        Flag[i] = true;

        //单边交错轨，或者Bi已经使用过
        if ( 0 == L[i] || dfs(L[i],nb) ){
            L[i] = node;
            return 1;
        }
    }
    return 0;
}
//na为A的数量，nb为B的数量
int Hungary(int na,int nb){
    fill(L,L+nb+1,0);

    int ret = 0;
    for(int i=1;i<=na;++i){
        fill(Flag,Flag+nb+1,false);
        ret += dfs(i,nb);
    }
    return ret;
}

int N,M,K;
bool read(){
    if ( EOF == scanf("%d%d%d",&N,&M,&K) ) return false;

    initGraph(N,M);
    int a,b;
    for(int i=0;i<K;++i){
        scanf("%d%d",&a,&b);
        Graph[a][b] = true;
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        int ans = Hungary(N,M);

        int ret = 0;
        //对每一条边，删除之后再做最大匹配
        for(int i=1;i<=N;++i)for(int j=1;j<=M;++j)if(Graph[i][j]){
            Graph[i][j] = false;
            if ( ans != Hungary(N,M) ) ++ret;
            Graph[i][j] = true;
        }

        printf("Board %d have %d important blanks for %d chessmen.\n",kase,ret,ans);
    }
    return 0;
}
