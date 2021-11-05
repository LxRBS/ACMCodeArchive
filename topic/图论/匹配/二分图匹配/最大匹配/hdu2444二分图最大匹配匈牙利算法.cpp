/*
    一群人，其中存在互相认识的某些对
    问：首先将这群人分成两组，要求同组人都不认识
    其次，安排每一对认识的人坐下，问最多能安排多少对
    第一问是判断二分图，第二问是二分图最大匹配
    特别要注意的是如果没有第一问直接问最大匹配，就不是二分图匹配而是一般图匹配
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

int Q[SIZE];
int Color[SIZE];
bool isOK(int vn){
    fill(Color,Color+vn+1,0);

    int u,v,head = 0, tail = 0;

    for(int i=1;i<=vn;++i)if(0==Color[i]){
        Color[Q[tail++] = i] = 1;

        while( head != tail ){
            u = Q[head++];
            for(v=1;v<=vn;++v)if(Graph[u][v]){
                if ( 0 == Color[v] ){
                    Color[Q[tail++] = v] = Color[u] ^ 3;
                }else if ( Color[v] == Color[u] ){
                    return false;
                }
            }
        }
    }
}

int N,M;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N,N);
    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        Graph[a][b] = Graph[b][a] = true;
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        if ( isOK(N) ){
            printf("%d\n",Hungary(N,N)/2);
        }else{
            printf("No\n");
        }
    }
    return 0;
}
