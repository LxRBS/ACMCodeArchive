/*
    N个学生，
    每个学生说了一个范围[X,Y]
    表示排名在该区间
    但有些人的说法是矛盾的
    问最多有多少个人没有矛盾
    如果有多个答案，输出学号序最大的
    在匈牙利算法中，搜索增广路的时候方向搜索即可
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>
using namespace std;

bool Graph[66][100010];//二分图矩阵
int L[100010];//Li为A中与Bi匹配的点
int LinkA[65];
bool Flag[100010];//Fi表示Bi是否已在增广路中，在一次搜索中

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
            LinkA[node] = i;
            return 1;
        }
    }
    return 0;
}
//na为A的数量，nb为B的数量
int Hungary(int na,int nb){
    fill(L,L+nb+1,0);
    fill(LinkA,LinkA+na+1,0);

    int ret = 0;
    //求序号尽可能大的最大匹配，反过来
    for(int i=na;i>=1;--i){
        fill(Flag,Flag+nb+1,false);
        ret += dfs(i,nb);
    }
    return ret;
}


int N,M;

bool read(){
    if ( 1 != scanf("%d",&N) ) return false;

    initGraph(N,100000);
    int x,y;
    M = 0;
    for(int i=1;i<=N;++i){
        scanf("%d%d",&x,&y);
        M = max(M,y);
        for(int j=x;j<=y;++j)Graph[i][j] = true;
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(;nofkase--;){
        read();
        int ans = Hungary(N,M);
        printf("%d\n",ans);
        bool flag = true;
        for(int i=1;i<=N;++i)if(LinkA[i]){
            if ( flag ){
                printf("%d",i);
                flag = false;
            }else{
                printf(" %d",i);
            }
        }
        putchar('\n');
    }
    return 0;
}
