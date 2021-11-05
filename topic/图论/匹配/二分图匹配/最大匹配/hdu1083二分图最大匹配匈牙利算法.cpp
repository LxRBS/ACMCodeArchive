/*
    N个学生，P个课程
    问是否可以从N个学生中挑出P个，使得恰好各代表一门课程
    就是问最大匹配数是否等于P
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
    fill(L,L+nb+1,0);
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
    int ret = 0;
    for(int i=1;i<=na;++i){
        fill(Flag,Flag+nb+1,false);
        ret += dfs(i,nb);
    }
    return ret;
}

int N,P;
bool read(){
    scanf("%d%d",&P,&N);

    initGraph(N,P);
    int n,a;
    for(int i=1;i<=P;++i){
        scanf("%d",&n);
        while(n--){
            scanf("%d",&a);
            Graph[a][i] = true;
        }
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        printf(P==Hungary(N,P)?"YES\n":"NO\n");
    }
    return 0;
}
