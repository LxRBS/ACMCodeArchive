/*
    n个人分m个组，每个人有若干组可以候选
    问怎么分使得最大的组人数最少

    对每一个限制，使用匈牙利算法求多重匹配
    最小的限制即为答案
*/

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
int const SIZE = 1010;

bool Graph[SIZE][SIZE];//二分图矩阵
int L[SIZE][SIZE];//Li为A中与Bi匹配的点的集合
int LCnt[SIZE];//目前与Bi相匹配的点的数量
bool Flag[SIZE];//Fi表示Bi是否已在增广路中，在一次搜索中

inline void initGraph(int na,int nb){
    memset(Graph,0,sizeof(Graph));
}

//node为A中的节点编号，从1开始
int dfs(int node,int nb,int limit){
    for(int i=1;i<=nb;++i){
        //如果没有边，或者已经在增广路上
        if ( !Graph[node][i] || Flag[i] ) continue;
        Flag[i] = true;

        if ( LCnt[i] < limit ){
            L[i][LCnt[i]++] = node;
            return 1;
        }

        for(int j=0;j<LCnt[i];++j)if ( dfs(L[i][j],nb,limit) ){
            L[i][j] = node;
            return 1;
        }
    }
    return 0;
}
//na为A的数量，nb为B的数量
int Hungary(int na,int nb,int limit){
    fill(LCnt,LCnt+nb+1,0);
    for(int i=1;i<=nb;++i)fill(L[i],L[i]+na+1,0);

    int ret = 0;
    for(int i=1;i<=na;++i){
        fill(Flag,Flag+nb+1,false);
        ret += dfs(i,nb,limit);
    }
    return ret;
}

int N,M;
char Input[5000];
bool read(){
    scanf("%d%d",&N,&M);
    if ( 0 == N && 0 == M ) return false;

    fgets(Input,4999,stdin);

    initGraph(N,M);

    for(int i=1;i<=N;++i){
        fgets(Input,4999,stdin);
        stringstream ss(Input);
        string name;
        ss>>name;
        int b;
        while(ss>>b){
            Graph[i][++b] = true;
        }
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        int left = 0,right = N,mid;

        do{
            mid = ( left + right ) >> 1;
            if ( Hungary(N,M,mid) == N ) right = mid - 1;
            else left = mid + 1;
        }while( left <= right );

        printf("%d\n",left);
    }
    return 0;
}
