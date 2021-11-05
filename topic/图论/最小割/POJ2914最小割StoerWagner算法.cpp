#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef int weight_t;
int const SIZE_OF_VERTIECES = 550;
weight_t const INF = 0x3F3F3F3F;

weight_t Graph[SIZE_OF_VERTIECES][SIZE_OF_VERTIECES];//图的邻接表，索引从1开始

inline void initGraph(int vn=0){
    memset(Graph,0,sizeof(Graph));
}

//收缩操作，求出本次搜索的最小割值以及S和T,O(N*N)
//w和flag、behalf是辅助数组，behalf[i]为真说明点i不是独立的而是被缩进了别的点中
weight_t contract(int vn,int&s,int&t,weight_t w[],bool flag[],bool behalf[]){
    fill(w,w+vn+1,0);
    fill(flag,flag+vn+1,false);

    weight_t ans;
    for(int j,k,i=1;i<=vn;++i){
        k = 0;
        //找到不在中间结果中且权值最大的点k
        for(j=1;j<=vn;++j)if(!behalf[j]&&!flag[j]&&(!k||w[j]>w[k])) k = j;
        if (!k) break;
        //滚动记录s和t，并且将k加入中间结果
        s = t; flag[t=k] = true;
        ans = w[k];
        for(j=1;j<=vn;++j)if(!behalf[j]&&!flag[j]) w[j] += Graph[k][j];
    }
    return ans;
}

//vn为顶点数量，w和flag、behalf是辅助数组
weight_t StoerWagner(int vn,weight_t w[],bool flag[],bool behalf[]){
    weight_t ans = INF;
    fill(behalf,behalf+vn+1,0);

    for(int s,t,i=1;i<vn;++i){
        ans = min(ans,contract(vn,s,t,w,flag,behalf));
        //说明图本身就不连通
        if ( 0 == ans ) return 0;
        //将t缩到s中
        behalf[t] = true;
        for(int j=1;j<=vn;++j)if(!behalf[j])Graph[s][j] += Graph[t][j],Graph[j][s] += Graph[j][t];
    }
    return ans;
}

int N,M;
bool read(){
    if ( 2!=scanf("%d%d",&N,&M) ) return false;
    initGraph();
    for(int a,b,c,i=0;i<M;++i){
        scanf("%d%d%d",&a,&b,&c);
        Graph[++a][++b] += c;
        Graph[b][a] += c;
    }
    return true;
}

bool F1[SIZE_OF_VERTIECES],F2[SIZE_OF_VERTIECES];
int W[SIZE_OF_VERTIECES];
int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        printf("%d\n",StoerWagner(N,W,F1,F2));
    }
    return 0;
}
