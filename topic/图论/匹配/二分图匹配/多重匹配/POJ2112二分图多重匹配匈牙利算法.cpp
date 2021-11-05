/*
    K个机器，C个牛
    每个机器能容纳最多M个牛
    牛到机器有个距离
    将牛分配到机器
    要求使得走的最远的牛走的距离最短
    从大到小，把每条边去掉，看匹配数能否到C
    去掉以后就不能匹配的是答案
*/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;
int const SIZE = 1010;

int Graph[SIZE][SIZE];//二分图矩阵
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

int K,C,M;
int D[240][240];
vector<int> W;
bool read(){
    if ( EOF == scanf("%d%d%d",&K,&C,&M) ) return false;

    for(int i=1;i<=K+C;++i)for(int j=1;j<=K+C;++j){
        scanf("%d",D[i]+j);
        if ( 0 == D[i][j] ) D[i][j] = 1000000000;
    }

    //Floyd算法求最短路
    for(int k=1;k<=K+C;++k)for(int i=1;i<=K+C;++i)for(int j=1;j<=K+C;++j)
        D[i][j] = min(D[i][j],D[i][k]+D[k][j]);

    //建图
    initGraph(C,K);
    for(int i=K+1;i<=K+C;++i)for(int j=1;j<=K;++j) {Graph[i-K][j] = D[i][j];W.push_back(D[i][j]);}

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        sort(W.begin(),W.end(),greater<int>());

        //应该使用二分法，这里就是用了暴力
        int ans;
        for(vector<int>::iterator it=W.begin();it!=W.end();++it){
            for(int i=1;i<=C;++i)for(int j=1;j<=K;++j)if(Graph[i][j]==*it)Graph[i][j]=0;
            if ( Hungary(C,K,M) != C ) {
                ans = *it;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
