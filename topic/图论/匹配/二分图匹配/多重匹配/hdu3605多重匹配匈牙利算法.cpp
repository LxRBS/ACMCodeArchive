/*
    n个人要住到m个星球上
    每个人有若干愿意居住的星球
    每个星球最多容纳ai个人
    是否能够进行分配
    
    使用多重匹配，刚好没有超时
    使用状态压缩应该更快 
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;


int Graph[100010][13];//二分图矩阵
int L[13][100010];//Li为A中与Bi匹配的点的集合
int LCnt[13];//目前与Bi相匹配的点的数量
bool Flag[13];//Fi表示Bi是否已在增广路中，在一次搜索中
int Limit[13];//Limit[i]为Bi的匹配数限制

inline void initGraph(int na,int nb){
    memset(Graph,0,sizeof(Graph));
}

//node为A中的节点编号，从1开始
int dfs(int node,int nb){
    for(int i=1;i<=nb;++i){
        //如果没有边，或者已经在增广路上
        if ( !Graph[node][i] || Flag[i] ) continue;
        Flag[i] = true;

        if ( LCnt[i] < Limit[i] ){
            L[i][LCnt[i]++] = node;
            return 1;
        }

        for(int j=0;j<LCnt[i];++j)if ( dfs(L[i][j],nb) ){
            L[i][j] = node;
            return 1;
        }
    }
    return 0;
}
//na为A的数量，nb为B的数量
int Hungary(int na,int nb){
    fill(LCnt,LCnt+nb+1,0);
    for(int i=1;i<=nb;++i)fill(L[i],L[i]+na+1,0);

    int ret = 0;
    for(int i=1;i<=na;++i){
        fill(Flag,Flag+nb+1,false);
        
        //这道题是判断最大匹配是否存在，因此只要有一次没有匹配就能够确定答案
        if ( 0 == dfs(i,nb) ) return ret;
        ret += 1;
    }
    return ret;
}


int N,M;
bool read(){
    if ( 2 != scanf("%d%d",&N,&M) ) return false;

    initGraph(N,M);

    for(int i=1;i<=N;++i){
        for(int j=1;j<=M;++j)scanf("%d",Graph[i]+j);
    }

    for(int i=1;i<=M;++i)scanf("%d",Limit+i);

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    while(read()){
        int ans = Hungary(N,M);
        printf(ans==N?"YES\n":"NO\n");
    }
    return 0;
}
