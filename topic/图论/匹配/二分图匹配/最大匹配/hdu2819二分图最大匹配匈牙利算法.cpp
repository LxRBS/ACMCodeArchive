/*
    给定一个01矩阵，可以互换两行、或者互换两列
    问能否通过操作将主对角线全变为1，输出操作
    按行列建边，看最大匹配是否为N
    输出操作稍微麻烦一点，可以按顺序进行
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

int N;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initGraph(N,N);

    int a;
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
        scanf("%d",&a);
        Graph[i][j] = a;
    }

    return true;
}

char Output[110][110];

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        if ( N != Hungary(N,N) ){
            printf("-1\n");
        }else{
            int ret = 0;
            //对每一行找到应该匹配的列，进行交换
            for(int i=1,j;i<=N;++i){
                j = 1;
                while( j <= N && L[j] != i ) ++j;

                if ( i != j ){
                    sprintf(Output[ret++],"C %d %d\n",i,j);
                    swap(L[i],L[j]);
                }

            }
            printf("%d\n",ret);
            for(int i=0;i<ret;++i)printf("%s",Output[i]);
        }
    }
    return 0;
}
