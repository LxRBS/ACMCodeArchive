//求二分图最大独立集的点的数量，二分图最大独立集=总点数-最大匹配
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;


int const SIZE = 1005;

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

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initGraph(N,N);
    int a,b,c;
    for(int i=1;i<=N;++i){
        a = getUnsigned() + 1;
        c = getUnsigned();
        for(int j=0;j<c;++j){
            b = getUnsigned() + 1;
            Graph[a][b] = true;
        }
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) printf("%d\n",N-Hungary(N,N)/2);
    return 0;
}
