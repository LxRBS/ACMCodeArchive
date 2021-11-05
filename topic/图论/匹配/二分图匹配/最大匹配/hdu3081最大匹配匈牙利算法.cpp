/*
    N个男孩和N个女孩
    每个女孩有一个备选的男孩列表
    每个女孩的朋友的备选也都是该女孩的备选
    做匹配，如果N个女孩都有匹配，就称完成了一轮
    问最多做多少轮
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 110;

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

struct ufs_t{
    enum{UF_SIZE=110};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int N,M,F;
bool read(){
    if ( 3 != scanf("%d%d%d",&N,&M,&F) ) return false;

    initGraph(N,N);
    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        Graph[a][b] = true;
    }

    UF.init(N);
    for(int i=0;i<F;++i){
        scanf("%d%d",&a,&b);
        UF.unite(a,b);
    }

    for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j)if(UF.find(i)==UF.find(j)){
        for(int k=1;k<=N;++k){
            if ( Graph[j][k] ) Graph[i][k] = true;
            if ( Graph[i][k] ) Graph[j][k] = true;
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

        int cnt = 0;
        while( Hungary(N,N) == N ){
            ++cnt;
            //删除已经使用过的匹配边
            for(int i=1;i<=N;++i) Graph[L[i]][i] = false;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
